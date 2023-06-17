/*
    This file is part of MNTG.
    MNTG is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation, either version 3 of
    the License, or (at your option) any later version.
    MNTG is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.
    You should have received a copy of the GNU Lesser General Public License
    along with MNTG.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    tuple<set<Node*>,map<int,int>,set<int>> nodes_tuple = generate_nodes(parameters,adaptation_functions); 
    set<Link*> links = generate_links(get<1>(nodes_tuple), get<2>(nodes_tuple));    
    check_connectivity(get<0>(nodes_tuple),links);
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
        graphs->at(i) = new Graph(); 
        graph_generator->read_graph(graphs->at(i),infilenames->at(i));
    }
}

/**
 * 
 */

void TopologyGenerator::generate_random_graphs(map<string,string> parameters)
{ 
    if (parameters["net_model"].compare("mono_random") == 0)
    {
        graphs = new vector<Graph*>(1);
    }
    else if (parameters["net_model"].compare("multi_random") == 0)
    {
        graphs = new vector<Graph*>(stoi(parameters["nb_protocols"]));
    }
    for (int i = 0; i < (int) graphs->size(); i++) 
    {
        graphs->at(i) = new Graph(); 
        if (parameters["graph_model"].compare("erdos_renyi") == 0) 
        {
            graph_generator->generate_erdos_renyi_graph(graphs->at(i),stoi(parameters["seed_nb"])+i, stoi(parameters[string("nb_nodes_g_").append(to_string(i))]), stof(parameters["p_connection"]));
        }
        else if (parameters["graph_model"].compare("barabasi_albert") == 0) 
        {
            graph_generator->generate_barabasi_albert_graph(graphs->at(i),stoi(parameters["seed_nb"])+i, stoi(parameters[string("nb_nodes_g_").append(to_string(i))]), stof(parameters["p_attachement"]), stoi(parameters["m_attachement"]));
        }
        else if (parameters["graph_model"].compare("watts_strogatz") == 0)
        {
            graph_generator->generate_watts_strogatz_graph(graphs->at(i),stoi(parameters["seed_nb"])+i, stoi(parameters[string("nb_nodes_g_").append(to_string(i))]), stof(parameters["p_beta"]), stoi(parameters["k_mean_degree"]));            
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

int TopologyGenerator::random_choice_graph(int seed_nb, vector<int>& graphs_list)
{
    srand(seed_nb);
    int g_index = rand() % (graphs_list.size());
    int g_id = graphs_list.at(g_index);
    if (graphs_list.size() > 1)
    {
        graphs_list.erase(graphs_list.begin()+g_index);
    }
    return g_id;
}

/**
 * 
 */

int TopologyGenerator::random_choice_vertex(int seed_nb, vector<int>& vertices_list)
{
    srand(seed_nb);
    int v_index = rand() % vertices_list.size();
    int v_id = vertices_list.at(v_index);
    vertices_list.erase(vertices_list.begin()+v_index);
    return v_id;
}



/**
 * 
 */

set<AdaptationFunction*> TopologyGenerator::generate_adaptation_functions_mono_random_node(map<string,string> parameters, int node_id, set<AdaptationFunction*> adaptation_functions)
{
    set<AdaptationFunction*> adaptation_functions_node;
    srand(stoi(parameters["seed_nb"])+node_id);
    float p_function;
    for(auto f : adaptation_functions)
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
    return adaptation_functions_node;
}

/**
 * 
 */

set<AdaptationFunction*> TopologyGenerator::generate_adaptation_functions_multi_random_node(map<string,string> parameters, int node_id, set<int> protocols, set<AdaptationFunction*> adaptation_functions)
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
    tuple<set<Node*>,map<int,int>,set<int>> nodes_tuple;
    if (parameters["net_model"].compare("mono_random") == 0)
    {
        nodes_tuple = generate_mono_random_nodes(parameters,adaptation_functions);

    }else if (parameters["net_model"].compare("multi_random") == 0)
    {
        nodes_tuple = generate_multi_random_nodes(parameters,adaptation_functions);
    }
    return nodes_tuple;
     
}


tuple<set<Node*>,map<int,int>,set<int>> TopologyGenerator::generate_mono_random_nodes(map<string,string> parameters,set<AdaptationFunction*> adaptation_functions)
{
    set<Node*> nodes;
    map<int,int> map_id;  
    set<int> unused_id;
    int new_id = 0;

    for(auto v_id : graph_generator->get_vertices_graph(graphs->front()) )
    {
        map_id.insert(make_pair(v_id,new_id));
        set<int> neighbors = graph_generator->get_neighbors(graphs->front(),v_id);
        set<AdaptationFunction*> adaptation_functions_node = generate_adaptation_functions_mono_random_node(parameters,new_id,adaptation_functions);
        if ( (!adaptation_functions_node.empty()) && (!neighbors.empty()) ) 
        {
            nodes.insert(new Node(new_id, neighbors, adaptation_functions_node));   
        }
        else 
        {
            unused_id.insert(v_id);
        }  
        new_id++;
    }
    return make_tuple(nodes,map_id,unused_id);      
}


tuple<set<Node*>,map<int,int>,set<int>> TopologyGenerator::generate_multi_random_nodes(map<string,string> parameters,set<AdaptationFunction*> adaptation_functions)
{
    set<Node*> nodes;
    map<int,int> map_id;  
    set<int> unused_id;
    int v_id, g_id;
    int new_id = 0;
    set<int> protocols;
    set<int> multi_id;
    set<int> neighbors;
    vector<vector<int>> vertices_list(graphs->size());  
    for (int i = 0; i < (int) graphs->size(); i++)
    {
        vertices_list.at(i) = graph_generator->get_vertices_graph(graphs->at(i));
    }

    for (int i = stoi(parameters["nb_protocols"]); i > 0 ; i--) 
    { 
       for (int j = 0; j < stoi(parameters[string("nb_nodes_p_").append(to_string(i))]); j++)
       {    
            neighbors.clear();
            protocols.clear();
            vector<int> graphs_list(graphs->size());
            iota(graphs_list.begin(), graphs_list.end(), 0);
            vector<int> protocols_list(stoi(parameters["nb_protocols"]));
            iota(protocols_list.begin(), protocols_list.end(), 0);
            for (int k = 0; k < i; k++)
            {   
                for (int g_index = 0; g_index < (int) graphs_list.size(); g_index++)
                {
                    if ( vertices_list.at(g_index).size() == 0) 
                        graphs_list.erase(graphs_list.begin()+g_index); 
                }
                g_id = random_choice_graph((stoi(parameters["seed_nb"])+i+j+k), graphs_list);
                v_id = random_choice_vertex((stoi(parameters["seed_nb"])+i+j+k+g_id), vertices_list.at(g_id));
                set<int> v_neighbors = graph_generator->get_neighbors(graphs->at(g_id),v_id);
                neighbors.insert(v_neighbors.begin(),v_neighbors.end());
                protocols.insert(g_id);
                map_id.insert(make_pair(v_id,new_id));
                multi_id.insert(v_id);
            }
            set<AdaptationFunction*> adaptation_functions_node = generate_adaptation_functions_multi_random_node(parameters,new_id,protocols,adaptation_functions);
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
            if ( (map_id[get<0>(e)] != map_id[get<1>(e)]) && (unused_vertices.find(get<0>(e)) == unused_vertices.end()) && (unused_vertices.find(get<1>(e)) == unused_vertices.end()) )
            {
                links.insert(new Link(map_id[get<0>(e)], map_id[get<1>(e)], get<2>(e)));   
            }    
        }
    }
    return links;
}

/**
 * 
 */

void TopologyGenerator::check_connectivity(set<Node*> nodes, set<Link*> links)
{
    // remove link duplicates 
    // reorder nodes id 
    int new_id = 0;
    map<int,int> map_id; 
    for(auto n : nodes)
    {
        map_id.insert(make_pair(n->get_id(),new_id));
        n->set_id(new_id); 
        new_id++;
    }
    for(auto l : links)
    {
        l->set_src(map_id[l->get_src()]); 
        l->set_dest(map_id[l->get_dest()]); 
    }
    // update neighbors
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
        network_file << "NODES (id [protocols] [adaptation_functions])" << endl;
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
                network_file << "("<< f->get_type() << ' ' << f->get_from() << ' ' << f->get_to() << ' ' << f->get_cost() << ") ";
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