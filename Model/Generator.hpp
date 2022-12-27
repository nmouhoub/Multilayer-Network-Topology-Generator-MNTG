#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include "Utils/TopologyGenerator.hpp"


class Generator
{
	private: 
		Network *network;
		TopologyGenerator *topo_generator; 
		
	public: 
		Generator() = default;
		Generator(char* gen_type, int rand_seed, int nb_nodes, int nb_links, float p_gen, 
			                int nb_protocols, float p_func);
		
		void set_network(Network *_network);
		
		Network* get_network();

		void write_topology(char *path);
		
		~Generator();
};

#endif