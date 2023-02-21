/**
 *
 */

#include "../include/Node.h"

/**
 *
 */

Node::Node(int _id, set<int> _neighbors, set<AdaptationFunction *> _adapt_functions)
{
	id = _id;
	adapt_functions = _adapt_functions;
	for(auto f : adapt_functions)
	{
		protocols.insert(f->get_from());
		protocols.insert(f->get_to());	
	}
	neighbors = _neighbors;
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

set<int> Node::get_protocols()
{
	return protocols;
}

/**
 *
 */

set<AdaptationFunction *> Node::get_adapt_functions()
{
	return adapt_functions;
}