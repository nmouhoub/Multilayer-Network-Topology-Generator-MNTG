#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <array>
#include <algorithm>
#include "Node.hpp"
#include "Link.hpp"

using namespace std;


class Network 
{
	private :    
		int diameter;
		set<Node*> nodes;
		set<Link*> links;
		set<Link*> undirected_links;
		set<char> protocols; 
		set<AdaptationFunction *> adapt_functions; 
		
	public : 
		Network(set<char> _protocols);
		Network(set<char> _protocols, set<AdaptationFunction*> _adapt_functions);

		set<Node*> get_nodes();
		set<Link*> get_links();
		set<Link*> get_undirected_links();
	    Node *get_node(int _id);
		set<char> get_protocols();
		int get_diameter();
		
		void set_diameter(int diam);
		void set_nodes(set<Node*> _nodes);
		void set_links(set<Link*> _links);
		void set_undirected_links(set<Link*> _undirected_links);
		set<AdaptationFunction*> get_adapt_functions();
		void set_adapt_functions(set<AdaptationFunction*> _adapt_functions);


		~Network();
};	

#endif