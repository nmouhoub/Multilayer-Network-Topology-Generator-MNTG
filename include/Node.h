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
		void set_id(int _id);
		set<int> get_neighbors();
	    set<int> get_protocols();
	    set<AdaptationFunction *> get_adapt_functions();
};

#endif