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

#ifndef LINK_H
#define LINK_H

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
		void set_src(int _src);
		void set_dest(int _dest);
};


#endif
