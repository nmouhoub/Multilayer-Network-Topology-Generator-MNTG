/**
 * 
 */

#include "../include/TopologyGenerator.h"

/**
 * 
 */

TopologyGenerator::TopologyGenerator()
{
    graph_generator = new GraphGenerator();
}

/**
 * 
 */

Network* TopologyGenerator::generate_mono_random_topology(char* gen_type, int rand_seed, int nb_nodes, int m_attach, int p_attach, int c_prob, int nb_protocols, float f_prob, int link_cost, int cv_cost, int ec_cost, int dc_cost)
{
    generate_mono_random_graph(gen_type, rand_seed, nb_nodes, m_attach, p_attach, c_prob);
    set<char> protocols = generate_protocols(nb_protocols);
    set<AdaptationFunction*> adaptation_functions = generate_adaptation_functions(protocols);
    set<Node*> nodes = generate_nodes(rand_seed, f_prob, adaptation_functions);
    set<Link*> links = generate_links(link_cost, cv_cost, ec_cost, dc_cost, nodes);
    Network *network = new Network(nodes, links, protocols, adaptation_functions);
    return network; 
}

/**
 * 
 */

void TopologyGenerator::generate_mono_random_graph(char* gen_type, int rand_seed, int nb_nodes, int m_attach, int p_attach, int c_prob)
{
    if (strcmp(gen_type,"ER") == 0) 
    {
        graph_generator->generate_erdos_renyi_graph(rand_seed, GNP, nb_nodes, c_prob, UnDirected, NoLoops);
    }
    else if (strcmp(gen_type,"BA") == 0) 
    {
        graph_generator->generate_barabasi_albert_graph(rand_seed, PSUMTREE, nb_nodes, p_attach, m_attach, 0, 0, 1, UnDirected, 0);
    }
    else
    {
        cerr << "error : generator type not defined !" << endl;
    } 
}

/**
 * 
 */

set<char> TopologyGenerator::generate_protocols(int nb_protocols)
{
    string valid_protocols = all_protocols.substr(0,nb_protocols);
    set<char> protocols;
    for(auto p : valid_protocols) {
        protocols.insert(p);
    }
    return protocols;
}

/**
 * 
 */

set<AdaptationFunction*> TopologyGenerator::generate_adaptation_functions(set<char> protocols)
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

/**
 * 
 */

set<AdaptationFunction*> TopologyGenerator::generate_adaptation_functions_node(set<AdaptationFunction*> adaptation_functions, float f_prob, int node_id, int rand_seed)
{
    set<AdaptationFunction*> adaptation_functions_node;
    srand(rand_seed+node_id);
    for(auto f : adaptation_functions)
    {
        if( (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) < f_prob) 
            adaptation_functions_node.insert(f);     
    }
    return adaptation_functions_node;
}

/**
 * 
 */

set<Node*> TopologyGenerator::generate_nodes(int rand_seed, float f_prob, set<AdaptationFunction*> adaptation_functions)
{
    set<Node*> nodes;
    for(auto v_id : graph_generator->get_vertices_graph() )
    {
        set<AdaptationFunction*> adaptation_functions_node = generate_adaptation_functions_node(adaptation_functions, f_prob, v_id, rand_seed);
        set<int> neighbors = graph_generator->get_neighbors(v_id);
        if ( (!adaptation_functions_node.empty()) && (!neighbors.empty()) ) 
        {
            nodes.insert(new Node(v_id, neighbors, adaptation_functions_node));   
        }
    }
    return nodes;
}

/**
 * 
 */

set<Link*> TopologyGenerator::generate_links(int link_cost, int cv_cost, int ec_cost, int dc_cost, set<Node*> nodes)
{
    set<Link*> links;

    for (auto e : graph_generator->get_edges_graph()) 
    {
        Node *node_src = get_node(nodes, e.first);
        Node *node_dest = get_node(nodes, e.second);

        if ((node_src != nullptr) && (node_dest != nullptr))
        {
            MapCost map_cost_src = MapCost();
            MapCost map_cost_dest = MapCost();
            Link *l1 = new Link(e.first, e.second);
            Link *l2 = new Link(e.second, e.first);

            for(auto f_src : node_src->get_adapt_functions() ) 
            {
                switch (f_src->get_type())
                {
                    case 0:
                    {
                        if (f_src->get_from() == f_src->get_to() )
                        {
                            map_cost_src.insert(make_pair(f_src, link_cost));
                        }
                        else
                        {
                            map_cost_src.insert(make_pair(f_src, cv_cost));
                        }
                        break;
                    }
                    case 1:
                    {
                        map_cost_src.insert(make_pair(f_src, ec_cost));
                        break;
                    }
                    case 2: 
                    {
                        map_cost_src.insert(make_pair(f_src, dc_cost));
                        break; 
                    }
                    default:
                    break;
                }
            }
            for(auto f_dest : node_dest->get_adapt_functions() ) 
            {   
                switch (f_dest->get_type())
                {
                    case 0:
                    {
                        if (f_dest->get_from() == f_dest->get_to() )
                        {
                            map_cost_dest.insert(make_pair(f_dest, link_cost));
                        }
                        else
                        {
                            map_cost_dest.insert(make_pair(f_dest, cv_cost));
                        }
                        break;
                    }
                    case 1:
                    {
                        map_cost_dest.insert(make_pair(f_dest, ec_cost));
                        break;
                    }
                    case 2: 
                    {
                        map_cost_dest.insert(make_pair(f_dest, dc_cost));
                        break; 
                    }
                    default:
                    break;
                }
            }

            l1->set_map_cost(map_cost_src);
            l2->set_map_cost(map_cost_dest);

            node_src->add_link_out(l1);
            node_src->add_link_in(l2);
            
            node_dest->add_link_in(l1);
            node_dest->add_link_out(l2);
            
            links.insert(l1);
            links.insert(l2);
        }
    }
    return links;
}


/**
 * 
 */

Node* TopologyGenerator::get_node(set<Node*> nodes, int _id)
{
	for(auto n : nodes)
	{
		if (n->get_id() == _id)
		{
			return n;
		}
	}	
	return nullptr;
}

/**
 * 
 */

void TopologyGenerator::write_topology(Network *network, char *out_path)
{
    ofstream topo_file;
    auto path = out_path + string{".txt"} ; 
    topo_file.open (path);
    if(!topo_file) 
    { 
       cerr <<"error : output file not defined !" << endl; 
    }
    else
    {
        topo_file << "MULTILAYER NETWORK (nb_of_nodes nb_of_links nb_of_protocols)" << endl;
        topo_file << network->get_nodes().size() << ' ' 
                  << network->get_links().size() << ' ' 
                  << network->get_protocols().size() << endl; 
        topo_file << endl;
        topo_file << "NODES (id_number list_of_protocols)" << endl;
        for(auto n : network->get_nodes())
        {
            topo_file << n->get_id() << endl;
        }
        topo_file << endl;
        topo_file << "LINKS (src_node dest_node list_of_adaptation_functions_with_costs)" << endl;
        for(auto l : network->get_links())
        {
            topo_file << l->get_src() << ' ' << l->get_dest() ;
            for(auto p : l->get_map_cost())
            {
                topo_file << ' ' << p.first->get_type() << ' ' << p.first->get_from() << ' ' << p.first->get_to()  
                << ' ' << p.second ;
            }
            topo_file << endl;
        }
        topo_file.close();
    }
}


/**
 * 
 */

/*
void TopologyGenerator::generate_new_id(Network *network)
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
}*/

/**
 * 
 */

TopologyGenerator::~TopologyGenerator()
{
    delete graph_generator;
}