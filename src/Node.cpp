/**
 *
 */

#include "../include/Node.h"

/**
 *
 */

Node::Node(int _id)
{
	id = _id;
}

/**
 *
 */

Node::Node(int _id, set<int> _neighbors, set<AdaptationFunction *> _adapt_functions)
{
	id = _id;
	adapt_functions = _adapt_functions;
	for(auto f : adapt_functions)
	{
		protocols_in.insert(f->get_from());
		protocols_out.insert(f->get_to());	
	}
	neighbors = _neighbors;
}

/**
 *
 */

void Node::add_neighbor(int _neighbor)
{
	neighbors.insert(_neighbor);
}

/**
 *
 */

void Node::add_link_in(Link *link)
{
	links_in.insert(make_pair(link->get_src(), link));
}

/**
 *
 */

void Node::add_link_out(Link *link)
{
	links_out.insert(make_pair(link->get_dest(), link));
}

/**
 *
 */

void Node::set_neighbors_id(set<int> _neighbors)
{
	neighbors = _neighbors;
}

/**
 *
 */

void Node::init_neighbors()
{
	neighbors.clear();
}

/**
 *
 */

void Node::set_id(int _id)
{
	id = _id;
}

/**
 *
 */

void Node::add_adapt_func(AdaptationFunction *adapt_func)
{
	adapt_functions.insert(adapt_func);
	protocols_in.insert(adapt_func->get_from());
	protocols_out.insert(adapt_func->get_to());
}

/**
 *
 */

void Node::set_adapt_functions(set<AdaptationFunction*> _adapt_functions)
{
	adapt_functions = _adapt_functions;
	for(auto f : adapt_functions)
	{
		if(f->get_type() == DC)
		{
			protocols_in.insert(f->get_to());
			protocols_out.insert(f->get_from());
		}
		protocols_in.insert(f->get_from());
		protocols_out.insert(f->get_to());	
	}
}

/**
 *
 */

int Node::get_id()
{
	return id;
}

/**
 *
 */

set<int> Node::get_neighbors_id()
{
	return neighbors;
}

/**
 *
 */

set<char> Node::get_protocols_in()
{
	return protocols_in;
}

/**
 *
 */

set<char> Node::get_protocols_out()
{
	return protocols_out;
}

/**
 *
 */

set<AdaptationFunction *> Node::get_adapt_functions()
{
	return adapt_functions;
}

/**
 *
 */

unordered_map<int, Link*> Node::get_links_in()
{
	return links_in;
}

/**
 *
 */

unordered_map<int, Link*> Node::get_links_out()
{
	return links_out;
}