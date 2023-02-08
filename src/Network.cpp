/**
 *
 */

#include "../include/Network.h"

/**
 *
 */

Network::Network(set<Node*> _nodes, set<Link*> _links, set<char> _protocols, set<AdaptationFunction*> _adaptation_functions)
{		
	nodes = _nodes;
	links = _links;
	protocols = _protocols;
	adaptation_functions = _adaptation_functions;
}


/**
 *
 */

set<Node*> Network::get_nodes()
{
	return nodes;
}

/**
 *
 */

set<Link*> Network::get_links()
{
	return links;
}

/**
 *
 */

set<char> Network::get_protocols()
{
	return protocols;
}


/**
 *
 */

set<AdaptationFunction*> Network::get_adaptation_functions()
{
	return adaptation_functions;
}

/**
 *
 */

void Network::set_nodes(set<Node*> _nodes)
{
	nodes = _nodes;
}

/**
 *
 */

void Network::set_links(set<Link*> _links)
{
	links = _links;
}


/**
 *
 */

void Network::set_protocols(set<char> _protocols)
{
	protocols = _protocols;
}


/**
 *
 */

void Network::set_adaptation_functions(set<AdaptationFunction*> _adaptation_functions)
{
	adaptation_functions = _adaptation_functions;
}

/**
 *
 */

Network::~Network() 
{	
	for(auto n : nodes) 
		delete n;
	for(auto l : links)
		delete l;
	for(auto f : adaptation_functions) 
		delete f;
}