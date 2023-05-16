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
		Node *get_node_id(int id); 
};	

#endif