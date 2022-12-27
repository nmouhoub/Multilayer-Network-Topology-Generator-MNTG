#include "Network.hpp"


Network::Network(set<char> _protocols)
{
	protocols = _protocols;
	diameter = 0;
}

Network::Network(set<char> _protocols, set<AdaptationFunction*> _adapt_functions)
{		
	protocols = _protocols;
	adapt_functions = _adapt_functions;
	diameter = 0;
}


set<Node*> Network::get_nodes()
{
	return nodes;
}

set<Link*> Network::get_links()
{
	return links;
}

set<Link*> Network::get_undirected_links()
{
	return undirected_links;
}

Node* Network::get_node(int _id)
{
	for(auto n : nodes)
	{
		if (n->get_id() == _id)
		{
			return n;
		}
	}	
	return nullptr;
}

set<char> Network::get_protocols()
{
	return protocols;
}

set<AdaptationFunction*> Network::get_adapt_functions()
{
	return adapt_functions;
}


int Network::get_diameter()
{
	return diameter;
}

void Network::set_diameter(int diam)
{
	diameter = diam;
}

void Network::set_nodes(set<Node*> _nodes)
{
	nodes = _nodes;
}

void Network::set_links(set<Link*> _links)
{
	links = _links;
}

void Network::set_undirected_links(set<Link*> _undirected_links)
{
	undirected_links = _undirected_links;
}

void Network::set_adapt_functions(set<AdaptationFunction*> _adapt_functions)
{
	adapt_functions = _adapt_functions;
}


Network::~Network() 
{	
	for(auto n : nodes) 
		delete n;
	for(auto l : links)
		delete l;
	for(auto f : adapt_functions) 
		delete f;
}