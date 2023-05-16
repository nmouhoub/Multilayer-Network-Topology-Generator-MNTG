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

#include "../include/Network.h"

/**
 *
 */

Network::Network(set<Node*> _nodes, set<Link*> _links, set<int> _protocols, set<AdaptationFunction*> _adaptation_functions)
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

set<int> Network::get_protocols()
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

Node* Network::get_node_id(int id)
{
	for(auto n : nodes)
	{
		if (n->get_id() == id)
		{
			return n;
		}
	}	
	return nullptr;
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