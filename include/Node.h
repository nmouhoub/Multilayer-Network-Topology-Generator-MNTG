/**
 *
 */

#ifndef NODE_H
#define NODE_H

#include <set>
#include "Link.h"
#include "AdaptationFunction.h"


using namespace std;


/**
 *
 */

class Node 
{
	private : 
    	int id; 	
	    set<int> neighbors;
	    set<char> protocols_in;  						
	    set<char> protocols_out;
	    unordered_map<int, Link*> links_in;
	    unordered_map<int, Link*> links_out;	
	    set<AdaptationFunction *> adapt_functions;

	public : 
		Node(int _id);
		Node(int _id, set<int> _neighbors, set<AdaptationFunction*> _adapt_functions);
		void add_link_in(Link *link);
		void add_link_out(Link *link);
		void add_neighbor(int _neighbor);
		void set_id(int _id);
		void set_neighbors_id(set<int> _neighbors);
		void init_neighbors();
		void add_adapt_func(AdaptationFunction *adapt_func);
		void set_adapt_functions(set<AdaptationFunction*> _adapt_functions);
		int get_id();
		set<int> get_neighbors_id();
	    set<char> get_protocols_in();
	    set<char> get_protocols_out();
	    set<AdaptationFunction *> get_adapt_functions();
	    unordered_map<int, Link*> get_links_in();
	    unordered_map<int, Link*> get_links_out();
};

#endif