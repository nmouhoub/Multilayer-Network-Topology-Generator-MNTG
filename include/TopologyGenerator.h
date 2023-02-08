/**
 *
 */

#ifndef TOPOLOGY_GENERATOR_H
#define TOPOLOGY_GENERATOR_H

#include <iomanip>
#include <string.h>
#include <sstream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>
#include "Network.h"
#include "GraphGenerator.h"

using namespace std;


const int default_cost = 1;                                 //
const string all_protocols = "abcdefghijklmnopqrstuvwxyz";  //


/**
 *
 */

class TopologyGenerator 
{
    private: 
        GraphGenerator *graph_generator;
        
    public:
        TopologyGenerator();
        Network* generate_mono_random_topology(char* gen_type, int rand_seed, int nb_nodes, int m_attach, int p_attach, int c_prob, int nb_protocols, int f_prob);
        void generate_mono_random_graph(char* gen_type, int rand_seed, int nb_nodes, int m_attach, int p_attach, int c_prob);
        set<char> generate_protocols(int nb_protocols);
        set<AdaptationFunction*> generate_adaptation_functions(set<char> protocols);
        set<AdaptationFunction*> generate_adaptation_functions_node(set<AdaptationFunction*> adaptation_functions, float f_prob, int node_id, int rand_seed);
        set<Node*> generate_nodes(int rand_seed, float f_prob, set<AdaptationFunction*> adaptation_functions);
        set<Link*> generate_links(int cost, set<Node*> nodes);
        Node* get_node(set<Node*> nodes, int _id);
        ~TopologyGenerator();
};

#endif