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
    generate_topology(parameters,infilenames);
    write_topology(out_file);
}

/**
 * 
 */

void TopologyGenerator::generate_topology(map<string, string> parameters, vector<string> *infilenames)
{
    if ((stoi(parameters["load_graphs"]) > 0))
    {
        read_graphs(parameters, infilenames);
    }
    else
    {
        generate_random_graphs(parameters);
    }  
    set<int> protocols = generate_protocols(parameters);
    set<AdaptationFunction*> adaptation_functions = generate_adaptation_functions(parameters,protocols);
    // TODO: for multi_real build 2D vector for common id from the file in : infilenames->at(stoi(parameters["nb_protocols"])+1)
    tuple<set<Node*>,map<int,int>,set<int>> nodes_tuple = generate_nodes(parameters,adaptation_functions); 
    set<Link*> links = generate_links(get<1>(nodes_tuple), get<2>(nodes_tuple));    
    network = new Network(get<0>(nodes_tuple),links,protocols,adaptation_functions);
}

/**
 * 
 */

void TopologyGenerator::read_graphs(map<string, string> parameters,vector<string> *infilenames)
{  
    graphs = new vector<Graph*>(stoi(parameters["load_graphs"]));
    for (int i = 0; i < stoi(parameters["load_graphs"]); i++) 
    {
        // TODO: string graph_tmp_file_i = reorder_graph_id(infilenames->at(i));
        // TODO: graph_generator->read_graph(graphs->at(i),graph_tmp_file_i);
        graphs->at(i) = new Graph(); 
        graph_generator->read_graph(graphs->at(i),infilenames->at(i));
    }
}

/**
 * 
 */

void TopologyGenerator::generate_random_graphs(map<string,string> parameters)
{ 
    graphs = new vector<Graph*>(stoi(parameters["nb_protocols"]));
    for (int i = 0; i < stoi(parameters["nb_protocols"]); i++) 
    {
        graphs->at(i) = new Graph(); 
        if (parameters["graph_model"].compare("erdos_renyi") == 0) 
        {
            graph_generator->generate_erdos_renyi_graph(graphs->at(i),stoi(parameters["seed_nb"])+i, (stoi(parameters["nb_nodes"])/stoi(parameters["nb_protocols"])), stof(parameters["p_connection"]));
        }
        else if (parameters["graph_model"].compare("barabasi_albert") == 0) 
        {
            graph_generator->generate_barabasi_albert_graph(graphs->at(i),stoi(parameters["seed_nb"])+i, (stoi(parameters["nb_nodes"])/stoi(parameters["nb_protocols"])), stof(parameters["p_attachement"]), stoi(parameters["m_attachement"]));
        }
    }
}

/**
 * 
 */

set<int> TopologyGenerator::generate_protocols(map<string,string> parameters)
{
    set<int> protocols;
    for (int p = 0; p < stoi(parameters["nb_protocols"]) ; p++)
    {
        protocols.insert(p);
    }
    return protocols;
}

/**
 * 
 */

set<AdaptationFunction*> TopologyGenerator::generate_adaptation_functions(map<string,string> parameters, set<int> protocols)
{
    set<AdaptationFunction*> adapt_functions;
    for (set<int>::iterator p1=protocols.begin(); p1!=protocols.end(); ++p1)
    {
        adapt_functions.insert(new AdaptationFunction("RT",*p1,*p1,stoi(parameters["retransmission_cost"])));
        adapt_functions.insert(new AdaptationFunction("EC",*p1,*p1,stoi(parameters["encapsulation_cost"])));
        adapt_functions.insert(new AdaptationFunction("DC",*p1,*p1,stoi(parameters["decapsulation_cost"])));
        for (set<int>::iterator p2=std::next(p1); p2!=protocols.end(); ++p2)
        {
            adapt_functions.insert(new AdaptationFunction("CV",*p1,*p2,stoi(parameters["conversion_cost"])));
            adapt_functions.insert(new AdaptationFunction("CV",*p2,*p1,stoi(parameters["conversion_cost"])));
            adapt_functions.insert(new AdaptationFunction("EC",*p1,*p2,stoi(parameters["encapsulation_cost"])));
            adapt_functions.insert(new AdaptationFunction("EC",*p2,*p1,stoi(parameters["encapsulation_cost"])));
            adapt_functions.insert(new AdaptationFunction("DC",*p1,*p2,stoi(parameters["decapsulation_cost"])));
            adapt_functions.insert(new AdaptationFunction("DC",*p2,*p1,stoi(parameters["decapsulation_cost"])));
        }
    }
    return adapt_functions;
}

/**
 * 
 */

int TopologyGenerator::random_choice_graph(int seed_nb, set<int> selected_graphs)
{
    srand(seed_nb);
    int g_id = rand() % (graphs->size());
    while (selected_graphs.find(g_id) != selected_graphs.end())
    {
        g_id = rand() % (graphs->size());
    }
    return g_id;
}

/**
 * 
 */

int TopologyGenerator::random_choice_vertex(int seed_nb, int g_id, set<int> selected_ids)
{
    srand(seed_nb);
    int nb_vertices = graph_generator->get_nb_vertices_graph(graphs->at(g_id));
    int v_id = rand() % nb_vertices;
    while (selected_ids.find(v_id) != selected_ids.end())
    {
        v_id = rand() % nb_vertices;
    }
    return v_id;
}

/**
 * 
 */

set<AdaptationFunction*> TopologyGenerator::generate_adaptation_functions_node(map<string,string> parameters, int node_id, set<int> protocols, set<AdaptationFunction*> adaptation_functions)
{
    set<AdaptationFunction*> adaptation_functions_node;
    srand(stoi(parameters["seed_nb"])+node_id);
    float p_function;
    for(auto f : adaptation_functions)
    {   
        if ((protocols.find(f->get_from()) != protocols.end()) && (protocols.find(f->get_to()) != protocols.end()))
        {
            if (f->get_type().compare("RT") == 0)
                p_function = stof(parameters["p_retransmission"]);
            else if (f->get_type().compare("CV") == 0)
                p_function = stof(parameters["p_conversion"]);
            else if (f->get_type().compare("EC") == 0)
                p_function = stof(parameters["p_encapsulation"]);
            else if (f->get_type().compare("DC") == 0)
                p_function = stof(parameters["p_decapsulation"]); 
            if( (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) < p_function) 
                adaptation_functions_node.insert(f);         
        }
    }
    return adaptation_functions_node;
}

/**
 * 
 */

tuple<set<Node*>,map<int,int>,set<int>> TopologyGenerator::generate_nodes(map<string,string> parameters,set<AdaptationFunction*> adaptation_functions)
{
    set<Node*> nodes;
    map<int,int> map_id;  
    set<int> unused_id;
    int v_id, g_id;
    int new_id = 0;
    set<int> protocols;
    set<int> multi_id;
    set<int> neighbors;
    set<int> selected_graphs;
    vector<set<int>> selected_ids(stoi(parameters["nb_protocols"]));  

    for (int i = 0; i < stoi(parameters["nb_protocols"]); i++)
    { 
       for (int j = 0; j < stoi(parameters[string("nb_nodes_").append(to_string(i+1))]); j++)
       {    
            neighbors.clear();
            protocols.clear();
            selected_graphs.clear();
            for (int k = 0; k <= i; k++)
            {   
                int l=0;
                g_id = random_choice_graph((stoi(parameters["seed_nb"])+i+j+k+l), selected_graphs);
                while ( (int) selected_ids.at(g_id).size() == graph_generator->get_nb_vertices_graph(graphs->at(g_id)))
                { 
                    l++;
                    g_id = random_choice_graph((stoi(parameters["seed_nb"])+i+j+k+l), selected_graphs);
                }
                v_id = random_choice_vertex((stoi(parameters["seed_nb"])+i+j+k+g_id), g_id, selected_ids.at(g_id));
                set<int> v_neighbors = graph_generator->get_neighbors(graphs->at(g_id),v_id);
                neighbors.insert(v_neighbors.begin(),v_neighbors.end());
                selected_ids.at(g_id).insert(v_id); 
                protocols.insert(g_id); 
                map_id.insert(make_pair(v_id,new_id));
                multi_id.insert(v_id);
                if (graphs->size() > 1) { selected_graphs.insert(g_id); }
            }
            set<AdaptationFunction*> adaptation_functions_node = generate_adaptation_functions_node(parameters,new_id,protocols,adaptation_functions);
            if ( (!adaptation_functions_node.empty()) && (!neighbors.empty()) ) 
            {
                nodes.insert(new Node(new_id, neighbors, adaptation_functions_node));   
            }
            else 
            {
                unused_id.insert(multi_id.begin(), multi_id.end());
            }  
            new_id++; 
            multi_id.clear();
       }
    }
    return make_tuple(nodes,map_id,unused_id);      
}

/**
 * 
 */

set<Link*> TopologyGenerator::generate_links(map<int,int> map_id, set<int> unused_vertices)
{
    set<Link*> links;
    for (int i = 0; i < (int) graphs->size(); i++)    
    {
        for (auto e : graph_generator->get_edges_graph(graphs->at(i))) 
        { 
            if ( (unused_vertices.find(get<0>(e)) == unused_vertices.end()) && (unused_vertices.find(get<1>(e)) == unused_vertices.end()) )
            {
                // TODO: detect duplicates
                links.insert(new Link(map_id[get<0>(e)], map_id[get<1>(e)], get<2>(e)));   
            }    
        }
    }
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
                network_file << p+1 << ' ' ;
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

TopologyGenerator::~TopologyGenerator()
{
    delete graph_generator;
    delete network;
    delete graphs; 
}