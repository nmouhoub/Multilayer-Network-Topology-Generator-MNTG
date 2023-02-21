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
	    set<int> protocols;  						
	    set<AdaptationFunction *> adapt_functions;

	public : 
		Node(int _id, set<int> _neighbors, set<AdaptationFunction*> _adapt_functions);
		int get_id();
		set<int> get_neighbors();
	    set<int> get_protocols();
	    set<AdaptationFunction *> get_adapt_functions();
};

#endif