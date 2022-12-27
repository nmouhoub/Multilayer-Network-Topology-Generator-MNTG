#include "Generator.hpp"


Generator::Generator(char* gen_type, int rand_seed, int nb_nodes, int nb_links, float p_gen, int nb_protocols, float p_func)
{
  topo_generator = new TopologyGenerator();
  network = topo_generator->generate_topology_from_parameters(gen_type, rand_seed, nb_nodes, nb_links, p_gen, nb_protocols, p_func);
}

void Generator::set_network(Network *_network)
{
	network = _network;
}

Network* Generator::get_network()
{
	return network;
}


void Generator::write_topology(char *path)
{
	topo_generator->write_graph_file(network, path);
	topo_generator->write_topology_file(network, path);
}


Generator::~Generator()
{
	delete topo_generator;
	delete network;
}