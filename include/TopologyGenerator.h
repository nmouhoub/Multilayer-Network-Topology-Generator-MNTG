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

#ifndef TOPOLOGY_GENERATOR_H
#define TOPOLOGY_GENERATOR_H

#include <iomanip>
#include <numeric>
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
        set<Link*> generate_links(map<int,int> map_id, set<int> unused_vertices);
        void check_connectivity(set<Node*> nodes, set<Link*> links);
        void write_topology(string file_name); 

        tuple<set<Node*>,map<int,int>,set<int>> generate_multi_random_nodes(map<string,string> parameters,set<AdaptationFunction*> adaptation_functions);
        tuple<set<Node*>,map<int,int>,set<int>> generate_mono_random_nodes(map<string,string> parameters,set<AdaptationFunction*> adaptation_functions);
        
        int random_choice_vertex(int seed_nb, vector<int>& vertices_list);
        int random_choice_graph(int seed_nb, vector<int>& graphs_list);
        
        set<AdaptationFunction*> generate_adaptation_functions_multi_random_node(map<string,string> parameters, int node_id, set<int> protocols, set<AdaptationFunction*> adaptation_functions);
        set<AdaptationFunction*> generate_adaptation_functions_mono_random_node(map<string,string> parameters, int node_id, set<AdaptationFunction*> adaptation_functions);
        
        ~TopologyGenerator();
};

#endif
