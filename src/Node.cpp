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

void Node::set_id(int _id)
{
	id = _id;
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