/**
 * 
 */

#include "../include/TopologyGenerator.h"

/**
 * 
 */

TopologyGenerator::TopologyGenerator(map<string, string> parameters, string out_file, vector<string> *infilenames)
{
    graph_generator = new GraphGenerator();
    if (parameters["net_model"].compare("mono_random") == 0)
    {
        graphs = new vector<Graph*>(1);
        generate_mono_random_topology(parameters,infilenames->front());

    }else if (parameters["net_model"].compare("multi_random") == 0)
    {
        graphs = new vector<Graph*>(stoi(parameters["nb_protocols"]));
        generate_multi_random_topology(parameters,infilenames);

    }else if (parameters["net_model"].compare("multi_real") == 0)
    {
        graphs = new vector<Graph*>(stoi(parameters["nb_protocols"]));
        //generate_multi_real_topology(parameters);

    }else 
    {
        cerr << "error : network generator type not defined !" << endl;
        exit(EXIT_FAILURE);
    }
    write_topology(out_file);
}

/**
 * 
 */

void TopologyGenerator::generate_mono_random_topology(map<string, string> parameters, string infilename)
{
    graphs->front() = new Graph();
    if (stoi(parameters["load_graphs"]) == 1)
    {
        read_graph(graphs->front(),infilename);
    }
    else
    {
        generate_random_graph(graphs->front(),parameters["graph_model"], stoi(parameters["seed_nb"]), stoi(parameters["nb_nodes"]), stoi(parameters["m_attachement"]), stof(parameters["p_attachement"]), stof(parameters["p_connection"]));
    }  
    set<int> protocols = generate_protocols(stoi(parameters["nb_protocols"]));
    set<AdaptationFunction*> adaptation_functions = generate_adaptation_functions(stoi(parameters["retransmission_cost"]), stoi(parameters["conversion_cost"]), stoi(parameters["encapsulation_cost"]), stoi(parameters["decapsulation_cost"]),protocols);
    tuple<set<Node*>,set<int>> nodes = generate_mono_random_nodes(stoi(parameters["seed_nb"]), stof(parameters["p_retransmission"]), stof(parameters["p_conversion"]), stof(parameters["p_encapsulation"]), stof(parameters["p_decapsulation"]), adaptation_functions);
    set<Link*> links = generate_mono_random_links(get<1>(nodes));
    network = new Network(get<0>(nodes), links, protocols, adaptation_functions);
}

/**
 * 
 */

void TopologyGenerator::generate_multi_random_topology(map<string, string> parameters, vector<string> *infilenames)
{
    for (int i = 0; i < stoi(parameters["nb_protocols"]); i++)
    {
        graphs->at(i) = new Graph(); 
        if (stoi(parameters["load_graphs"]) > 1)
        {
            read_graph(graphs->at(i),infilenames->at(i));
        }
        else
        {
            generate_random_graph(graphs->at(i),parameters["graph_model"], stoi(parameters["seed_nb"])+i, stoi(parameters["nb_nodes"]), stoi(parameters["m_attachement"]), stof(parameters["p_attachement"]), stof(parameters["p_connection"]));
        }   
    }
    set<int> protocols = generate_protocols(stoi(parameters["nb_protocols"]));
    set<AdaptationFunction*> adaptation_functions = generate_adaptation_functions(stoi(parameters["retransmission_cost"]), stoi(parameters["conversion_cost"]), stoi(parameters["encapsulation_cost"]), stoi(parameters["decapsulation_cost"]),protocols);
    //tuple<set<Node*>,set<int>> nodes = generate_mono_random_nodes(stoi(parameters["seed_nb"]), stof(parameters["p_retransmission"]), stof(parameters["p_conversion"]), stof(parameters["p_encapsulation"]), stof(parameters["p_decapsulation"]), adaptation_functions);
    //set<Link*> links = generate_mono_random_links(get<1>(nodes));
    //network = new Network(get<0>(nodes), links, protocols, adaptation_functions);
}


/**
 * 
 */

void TopologyGenerator::read_graph(Graph *g, string infilename)
{ 
    graph_generator->read_graph(g,infilename);
}

/**
 * 
 */

void TopologyGenerator::generate_random_graph(Graph *g, string gen_type, int rand_seed, int nb_nodes, int m_attach, int p_attach, int c_prob)
{
    if (gen_type.compare("erdos_renyi") == 0) 
    {
        graph_generator->generate_erdos_renyi_graph(g,rand_seed, nb_nodes, c_prob);
    }
    else if (gen_type.compare("barabasi_albert") == 0) 
    {
        graph_generator->generate_barabasi_albert_graph(g,rand_seed, nb_nodes, p_attach, m_attach);
    }
    else
    {
        cerr << "error: graph generator type not defined !" << endl;
        exit(EXIT_FAILURE);
    } 
}

/**
 * 
 */

set<int> TopologyGenerator::generate_protocols(int nb_protocols)
{
    set<int> protocols;
    for (int p = 1; p < nb_protocols+1 ; p++)
    {
        protocols.insert(p);
    }
    return protocols;
}

/**
 * 
 */

set<AdaptationFunction*> TopologyGenerator::generate_adaptation_functions(int retransmission_cost, int conversion_cost, int encapsulation_cost, int decapsulation_cost, set<int> protocols)
{
    set<AdaptationFunction*> adapt_functions;
    for (set<int>::iterator p1=protocols.begin(); p1!=protocols.end(); ++p1)
    {
        adapt_functions.insert(new AdaptationFunction("RT",*p1,*p1,retransmission_cost));
        adapt_functions.insert(new AdaptationFunction("EC",*p1,*p1,encapsulation_cost));
        adapt_functions.insert(new AdaptationFunction("DC",*p1,*p1,decapsulation_cost));
        for (set<int>::iterator p2=std::next(p1); p2!=protocols.end(); ++p2)
        {
            adapt_functions.insert(new AdaptationFunction("CV",*p1,*p2,conversion_cost));
            adapt_functions.insert(new AdaptationFunction("CV",*p2,*p1,conversion_cost));
            adapt_functions.insert(new AdaptationFunction("EC",*p1,*p2,encapsulation_cost));
            adapt_functions.insert(new AdaptationFunction("EC",*p2,*p1,encapsulation_cost));
            adapt_functions.insert(new AdaptationFunction("DC",*p1,*p2,decapsulation_cost));
            adapt_functions.insert(new AdaptationFunction("DC",*p2,*p1,decapsulation_cost));
        }
    }
    return adapt_functions;
}

/**
 * 
 */

set<AdaptationFunction*> TopologyGenerator::generate_adaptation_functions_node(set<AdaptationFunction*> adaptation_functions, float p_retransmission, float p_conversion, float p_encapsulation, float p_decapsulation, int node_id, int rand_seed)
{
    set<AdaptationFunction*> adaptation_functions_node;
    srand(rand_seed+node_id);
    float p_function;
    for(auto f : adaptation_functions)
    {
        if (f->get_type().compare("RT") == 0)
            p_function = p_retransmission;
        else if (f->get_type().compare("CV") == 0)
            p_function = p_conversion;
        else if (f->get_type().compare("EC") == 0)
            p_function = p_encapsulation;
        else if (f->get_type().compare("DC") == 0)
            p_function = p_decapsulation;
        else 
        {
            cerr << "error: function type not defined !" << endl; 
            exit(EXIT_FAILURE);
        }
        if( (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) < p_function) 
                adaptation_functions_node.insert(f);           
    }
    return adaptation_functions_node;
}

/**
 * 
 */

tuple<set<Node*>,set<int>> TopologyGenerator::generate_mono_random_nodes(int rand_seed, float p_retransmission, float p_conversion, float p_encapsulation, float p_decapsulation, set<AdaptationFunction*> adaptation_functions)
{
    set<Node*> nodes;
    set<int> unused;
    for(auto v_id : graph_generator->get_vertices_graph(graphs->front()) )
    {
        set<AdaptationFunction*> adaptation_functions_node = generate_adaptation_functions_node(adaptation_functions, p_retransmission, p_conversion, p_encapsulation, p_decapsulation, v_id, rand_seed);
        set<int> neighbors = graph_generator->get_neighbors(graphs->front(),v_id);
        if ( (!adaptation_functions_node.empty()) && (!neighbors.empty()) ) 
        {
            nodes.insert(new Node(v_id, neighbors, adaptation_functions_node));   
        }
        else 
        {
            unused.insert(v_id);
        }
    }
    return make_tuple(nodes,unused);
}

/**
 * 
 */

set<Link*> TopologyGenerator::generate_mono_random_links(set<int> unused_vertices)
{
    set<Link*> links;
    for (auto e : graph_generator->get_edges_graph(graphs->front())) 
    {
        if ( (unused_vertices.find(get<0>(e)) == unused_vertices.end()) && (unused_vertices.find(get<1>(e)) == unused_vertices.end()) )
        {
            links.insert(new Link(get<0>(e), get<1>(e), get<2>(e)));    
        }    
    }
    graph_generator->delete_vertices(graphs->front(),unused_vertices);
    return links;
}


/**
 * 
 */

void TopologyGenerator::write_topology(string file_name)
{
    ofstream network_file; 
    network_file.open(file_name, ios::out);
    if(!network_file) 
    { 
       cerr <<"error : output file not defined !" << endl; 
       exit(EXIT_FAILURE);
    }
    else
    {
        network_file << "MULTILAYER NETWORK (nb_of_nodes nb_of_links nb_of_protocols)" << endl;
        network_file << network->get_nodes().size() << ' ' 
                  << network->get_links().size() << ' ' 
                  << network->get_protocols().size() << endl; 
        network_file << endl;
        network_file << "NODES (id protocols adaptation_functions)" << endl;
        for(auto n : network->get_nodes())
        {
            network_file << n->get_id() << " [ ";
            for(auto p : n->get_protocols())
            {
                network_file << p << ' ' ;
            }
            network_file << "] [ " ;
            for(auto f : n->get_adapt_functions())
            {
                network_file << "("<< f->get_type() << ' ' << f->get_from() << ' ' << f->get_to() << ") ";
            }
            network_file << "]"<< endl;
        }
        network_file << endl;
        network_file << "LINKS (source destination cost)" << endl;
        for(auto l : network->get_links())
        {
            network_file << l->get_src() << ' ' << l->get_dest() << ' ' << l->get_cost() << endl;
        }
        network_file.close();
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
    delete network;
    delete graphs; 
}