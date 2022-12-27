#include "TopologyGenerator.hpp"


TopologyGenerator::TopologyGenerator()
{
    graph_generator = new GraphGenerator();
    nb_a = 0;
    nb_b = 0;
    nb_ab = 0;
}

Network* TopologyGenerator::generate_topology_from_parameters(char* gen_type, int rand_seed, int nb_nodes, int nb_links, float p_gen, 
                                                                        int nb_protocols, float p_func)
{
    generate_graph(gen_type, rand_seed, nb_nodes, nb_links, p_gen);
    set<char> protocols = generate_valid_protocols(nb_protocols);
    set<AdaptationFunction*> adapt_functions = generate_valid_adapt_functions(protocols);
    
    Network *network = new Network(protocols, adapt_functions);
    generate_nodes(network, p_func,rand_seed);
    generate_links(network, default_cost);
    generate_new_ids(network);
    compute_diameter(network);
    return network;
}


void TopologyGenerator::generate_graph(char* gen_type, int rand_seed, int nb_nodes, int nb_links, float p_gen)
{
    if (strcmp(gen_type, "ER") == 0)
    {
        graph_generator->generate_erdos_renyi_graph(rand_seed, GNP, nb_nodes, p_gen, UnDirected, NoLoops);
    }
    else
    {
        graph_generator->generate_barabasi_albert_graph(rand_seed, PSUMTREE,nb_nodes, p_gen, nb_links, 0, 0, 1, UnDirected, 0);   
    }
}

set<char> TopologyGenerator::generate_valid_protocols(int nb_protocols)
{
    string valid_protocols = all_protocols.substr(0,nb_protocols);
    set<char> protocols;
    for(auto p : valid_protocols) {
        protocols.insert(p);
    }
    return protocols;
}

set<AdaptationFunction*> TopologyGenerator::generate_valid_adapt_functions(set<char> protocols)
{
    set<AdaptationFunction*> adapt_functions;
    for (set<char>::iterator p1=protocols.begin(); p1!=protocols.end(); ++p1)
    {
        adapt_functions.insert(new AdaptationFunction(CV,*p1,*p1));
        adapt_functions.insert(new AdaptationFunction(EC,*p1,*p1));
        adapt_functions.insert(new AdaptationFunction(DC,*p1,*p1));
        for (set<char>::iterator p2=std::next(p1); p2!=protocols.end(); ++p2)
        {
            adapt_functions.insert(new AdaptationFunction(CV,*p1,*p2));
            adapt_functions.insert(new AdaptationFunction(CV,*p2,*p1));
            adapt_functions.insert(new AdaptationFunction(EC,*p1,*p2));
            adapt_functions.insert(new AdaptationFunction(EC,*p2,*p1));
            adapt_functions.insert(new AdaptationFunction(DC,*p1,*p2));
            adapt_functions.insert(new AdaptationFunction(DC,*p2,*p1));
        }
    }
    return adapt_functions;
}

set<AdaptationFunction*> TopologyGenerator::generate_adapt_functions_node(set<AdaptationFunction*> adapt_functions, float p_func, int node_id, int rand_seed)
{
    srand(rand_seed+node_id);
    set<AdaptationFunction*> adapt_functions_node;
    for(auto f : adapt_functions)
    {
        if( (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) < p_func) 
            adapt_functions_node.insert(f);     
    }
    return adapt_functions_node;
}

void TopologyGenerator::generate_nodes(Network* network, float p_func, int rand_seed)
{
    set<Node*> nodes;
    set<AdaptationFunction*> adapt_functions = network->get_adapt_functions();
    for(auto v_id : graph_generator->get_vertices_graph() )
    {
        set<AdaptationFunction*> adapt_funcs_node = generate_adapt_functions_node(adapt_functions, p_func, v_id, rand_seed);
        set<int> neighbors = graph_generator->get_neighbors(v_id);
        if ( (!adapt_funcs_node.empty()) && (!neighbors.empty()) ) 
        {
            nodes.insert(new Node(v_id, neighbors, adapt_funcs_node));   
        }
    }
    network->set_nodes(nodes);
}

void TopologyGenerator::generate_links(Network* network, int cost)
{
    set<Link*> links, undirected_links;

    for (auto e : graph_generator->get_edges_graph()) 
    {
        Node *node_src = network->get_node(e.first);
        Node *node_dest = network->get_node(e.second);

        if ((node_src != nullptr) && (node_dest != nullptr))
        {
            MapCost map_cost_src = MapCost();
            MapCost map_cost_dest = MapCost();
            Link *l1 = new Link(e.first, e.second);
            Link *l2 = new Link(e.second, e.first);

            for(auto f_src : node_src->get_adapt_functions() ) 
            {
                map_cost_src.insert(make_pair(f_src, cost));

            }
            for(auto f_dest : node_dest->get_adapt_functions() ) 
            {   
                map_cost_dest.insert(make_pair(f_dest, cost));
            }

            l1->set_map_cost(map_cost_src);
            l2->set_map_cost(map_cost_dest);

            node_src->add_link_out(l1);
            node_src->add_link_in(l2);
            
            node_dest->add_link_in(l1);
            node_dest->add_link_out(l2);

            undirected_links.insert(l1);
            links.insert(l1);
            links.insert(l2);
        }
    }
    network->set_links(links);
    network->set_undirected_links(undirected_links);
}


void TopologyGenerator::generate_new_ids(Network *network)
{
    map<int, int> map_ids;
    map<int,int>::iterator it_src, it_dest;

    set<Node*> nodes; 
    for (auto n : network->get_nodes())
    {
        if ( (!n->get_links_in().empty()) || (!n->get_links_out().empty()) )
        {
            nodes.insert(n);
        }
    }
    network->set_nodes(nodes);

    int id = 0;
    for (auto n : network->get_nodes())
    {
        map_ids.insert(make_pair(n->get_id(), id));
        n->set_id(id);
        n->init_neighbors();
        id++;
    }
    
    set<Link*> links; 
    for (auto l : network->get_links())
    {
        it_src = map_ids.find(l->get_src());
        it_dest = map_ids.find(l->get_dest());

        if ( (it_src != map_ids.end()) && (it_dest != map_ids.end()) )
        {
            l->set_src(it_src->second);
            l->set_dest(it_dest->second);

            network->get_node(l->get_src())->add_neighbor(l->get_dest());
            network->get_node(l->get_dest())->add_neighbor(l->get_src());
            links.insert(l);
        }
    }
    network->set_links(links);
}

void TopologyGenerator::write_graph_file(Network *network, char *out_path)
{
    ofstream out_file;
    auto path = out_path + string{".dot"} ; 
    out_file.open(path);
    if(!out_file) 
    { 
       cerr <<"Error in creating output file !" << endl; 
    }
    else
    {
        out_file << "graph {" << endl;

        for(auto n : network->get_nodes())
        {
            out_file << n->get_id() << " " ;

            // merge protocols in and out 
            for (auto p : n->get_protocols_in())
            {
                n->get_protocols_out().insert(p);
            }
            
            if (n->get_protocols_out().size() == 2)
            {
                out_file << "[style = filled fillcolor = blue];" << endl; 
                nb_ab++;
            }

            if (n->get_protocols_out().size() == 1)
            {
                if( (* (n->get_protocols_out().begin()) ) == 'a')
                {
                    out_file << "[style = filled fillcolor = red];" << endl;
                    nb_a++;
                }
                else
                {
                    out_file << "[style = filled fillcolor = yellow];" << endl;
                    nb_b++;
                }
            }
        }

        for(auto l : network->get_undirected_links())
        {
            out_file << l->get_src() << " -- " << l->get_dest() << ";" << endl;
        }

        out_file << "}" << endl;
        
        out_file.close(); 
        //system("sfdp -x -Goverlap=scale -Tpng Topologies/topo.dot > Topologies/topo.png");
    }
}

void TopologyGenerator::write_topology_file(Network *network, char *out_path)
{
    ofstream topo_file;
    auto path = out_path + string{".txt"} ; 
    topo_file.open (path);
    if(!topo_file) 
    { 
       cerr <<"Error in creating output file !" << endl; 
    }
    else
    {
        topo_file << "a only nodes = " << setprecision(2) << fixed << ( (float) nb_a  / (float) network->get_nodes().size() ) * 100 << " %" << endl;
        topo_file << "b only nodes = " << setprecision(2) << fixed << ( (float) nb_b  / (float) network->get_nodes().size() ) * 100 << " %" << endl;
        topo_file << "a/b nodes = " << setprecision(2) << fixed << ( (float) nb_ab / (float) network->get_nodes().size() ) * 100 << " %" << endl;
        topo_file << "diameter = " << network->get_diameter() << endl;
        topo_file << "==================" << endl;

        topo_file << network->get_nodes().size() << ' ' 
                  << network->get_links().size() << ' ' 
                  << network->get_protocols().size() << endl; 
        topo_file << "==================" << endl;
        for(auto n : network->get_nodes())
        {
            topo_file << n->get_id() << endl;
        }
        topo_file << "==================" << endl;
        for(auto l : network->get_links())
        {
            for(auto p : l->get_map_cost())
            {
                topo_file << '(' << l->get_src() << " -> " << l->get_dest() << ')' 
                          << ' ' << p.first->get_type() << ' ' << p.first->get_from() << ' ' << p.first->get_to()  
                          << ' ' << p.second << endl;
            }
            topo_file << "==================" << endl;
        }
        topo_file.close();
    }
}



int TopologyGenerator::compute_classical_bf(Network *network, int s)
{
    set<Node*> nodes = network->get_nodes();
	vector<int> *dist = new vector<int>(nodes.size());
	for (auto n: nodes)
	{
		dist->at(n->get_id()) = (int) nodes.size() * 2 ; 
	}
	dist->at(s) = 0; 

	for (int i = 1; i < (int) nodes.size(); i++)
	{
		for(auto u : nodes)
		{
			int u_id = u->get_id();

			for(auto v_id : u->get_neighbors_id())
			{
				if ( dist->at(v_id) > ( dist->at(u_id) + 1) )
				{
					dist->at(v_id) =  dist->at(u_id) + 1;
				}
			}
		}
	}
	int max_dist = 0;

	for(vector<int>::iterator it = dist->begin(); it != dist->end(); ++it) 
	{
    	if ( (*it > max_dist) && (*it != (int) network->get_nodes().size() * 2 ) )
    	{
    		max_dist = *it;
    	}
	}

	return max_dist;
}



void TopologyGenerator::compute_diameter(Network *network)
{
    set<int> delete_ids;
    int graph_diameter = 0;

    for (auto n: network->get_nodes())
	{
		int max_dist = compute_classical_bf(network,n->get_id());

        if (max_dist > graph_diameter)
        {
            graph_diameter = max_dist;
        }
        
	}

    network->set_diameter(graph_diameter);
}



TopologyGenerator::~TopologyGenerator()
{
    delete graph_generator;
}