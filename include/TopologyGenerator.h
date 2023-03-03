/**
 *
 */

#ifndef TOPOLOGY_GENERATOR_H
#define TOPOLOGY_GENERATOR_H

#include <iomanip>
#include <string.h>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <map>
#include <tuple>
#include <vector>
#include "Network.h"
#include "GraphGenerator.h"

using namespace std;

/**
 *
 */

class TopologyGenerator 
{
    private: 
        GraphGenerator *graph_generator;
        vector<Graph*> *graphs;
        Network *network;
        
    public:
        TopologyGenerator(map<string, string> parameters, string out_file, vector<string> *infilenames);
        void generate_topology(map<string, string> parameters, vector<string> *infilenames);
        void read_graphs(map<string, string> parameters,vector<string> *infilenames);
        void generate_random_graphs(map<string, string> parameters);
        set<int> generate_protocols(map<string, string> parameters);
        set<AdaptationFunction*> generate_adaptation_functions(map<string,string> parameters,set<int> protocols);
        tuple<set<Node*>,map<int,int>,set<int>> generate_nodes(map<string,string> parameters,set<AdaptationFunction*> adaptation_functions);
        int random_choice_vertex(int seed_nb, int g_id, set<int> selected_ids);
        int random_choice_graph(int seed_nb, set<int> selected_graphs);
        set<AdaptationFunction*> generate_adaptation_functions_node(map<string,string> parameters, int node_id, set<int> protocols, set<AdaptationFunction*> adaptation_functions);
        set<Link*> generate_links(map<int,int> map_id, set<int> unused_vertices);
        void write_topology(string file_name); 
        ~TopologyGenerator();
};

#endif