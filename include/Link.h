/**
 *
 */

#ifndef LINK_H
#define LINK_H

#include <utility> 
#include <unordered_map>
#include "../include/AdaptationFunction.h"

using namespace std;

/**
 *
 */


class Link
{
	private : 
		int src; 
		int dest; 
		int cost;

	public :
		Link(int _src, int _dest, int _cost);
		int get_src();
		int get_dest();	
		int get_cost();
};


#endif