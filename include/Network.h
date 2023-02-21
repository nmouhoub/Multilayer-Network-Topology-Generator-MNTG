/**
 *
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <array>
#include <algorithm>
#include "Node.h"
#include "Link.h"

using namespace std;

/**
 *
 */

class Network 
{
	private :    
		set<Node*> nodes;
		set<Link*> links;
		set<int> protocols; 
		set<AdaptationFunction *> adaptation_functions; 
		
	public : 
		Network(set<Node*> _nodes, set<Link*> _links, set<int> _protocols, set<AdaptationFunction*> _adaptation_functions);
		set<Node*> get_nodes();
		set<Link*> get_links();
		set<int> get_protocols();
		set<AdaptationFunction*> get_adaptation_functions();
		~Network();
};	

#endif