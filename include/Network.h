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
		set<char> protocols; 
		set<AdaptationFunction *> adaptation_functions; 
		
	public : 
		Network(set<Node*> _nodes, set<Link*> _links, set<char> _protocols, set<AdaptationFunction*> _adaptation_functions);
		set<Node*> get_nodes();
		set<Link*> get_links();
		set<char> get_protocols();
		set<AdaptationFunction*> get_adaptation_functions();
		void set_nodes(set<Node*> _nodes);
		void set_links(set<Link*> _links);
		void set_protocols(set<char> _protocols);
		void set_adaptation_functions(set<AdaptationFunction*> _adaptation_functions);
		~Network();
};	

#endif