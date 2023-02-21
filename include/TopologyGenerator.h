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

        void generate_mono_random_topology(map<string, string> parameters, string infilename);
        void generate_multi_random_topology(map<string, string> parameters, vector<string> *infilenames);
        
        void read_graph(Graph *g, string infilename);
        void generate_random_graph(Graph *g, string gen_type, int rand_seed, int nb_nodes, int m_attach, int p_attach, int c_prob);
        
        tuple<set<Node*>,set<int>> generate_mono_random_nodes(int rand_seed, float p_retransmission, float p_conversion, float p_encapsulation, float p_decapsulation, set<AdaptationFunction*> adaptation_functions);
        set<Link*> generate_mono_random_links(set<int> unused_vertices);

        set<int> generate_protocols(int nb_protocols);
        set<AdaptationFunction*> generate_adaptation_functions(int retransmission_cost, int conversion_cost, int encapsulation_cost, int decapsulation_cost,set<int> protocols);
        set<AdaptationFunction*> generate_adaptation_functions_node(set<AdaptationFunction*> adaptation_functions, float p_retransmission, float p_conversion, float p_encapsulation, float p_decapsulation, int node_id, int rand_seed);
       
        void write_topology(string file_name); 
        ~TopologyGenerator();
};

#endif