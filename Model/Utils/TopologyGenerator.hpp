#ifndef TOPOLOGY_GENERATOR_HPP
#define TOPOLOGY_GENERATOR_HPP

#include <iomanip>
#include <string.h>
#include <sstream>
#include <fstream>
#include <map>
#include <tuple>
#include <vector>

#include "../Network.hpp"
#include "GraphGenerator.hpp"

using namespace std;

const int default_cost = 1;
const string all_protocols = "abcdefghijklmnopqrstuvwxyz";


class TopologyGenerator 
{
    private: 
        GraphGenerator *graph_generator;
        int nb_a, nb_b, nb_ab; 
    public:
        TopologyGenerator();
        ~TopologyGenerator();

        void generate_links(Network *network, int cost);
        void generate_nodes(Network *network, float p_func, int rand_seed);

        void generate_new_ids(Network *network);

        set<char> generate_valid_protocols(int nb_protocols);
        set<AdaptationFunction*> generate_valid_adapt_functions(set<char> protocols);
        set<AdaptationFunction*> generate_adapt_functions_node(set<AdaptationFunction*> adapt_functions, float p_func, int node_id, int rand_seed);

        void generate_graph(char* gen_type, int rand_seed, int nb_nodes, int nb_links, float p_gen);
        Network* generate_topology_from_parameters(char* gen_type, int rand_seed, int nb_nodes, int nb_links, float p_gen, 
                                                            int nb_protocols, float p_func);

        int compute_classical_bf(Network *network, int s);
        void compute_diameter(Network *network);

        void write_graph_file(Network *network, char *out_path);
        void write_topology_file(Network *network, char *out_path);

};


#endif