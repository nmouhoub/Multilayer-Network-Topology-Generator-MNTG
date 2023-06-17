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

#ifndef ADAPTATION_FUNCTION_H
#define ADAPTATION_FUNCTION_H

#include <string>

using namespace std;

/**
 *
 */

class AdaptationFunction
{
    private:
	    string type; 
		int from; 
		int to;
		int cost;  

    public:		
    	AdaptationFunction(string _type, int _from, int _to, int _cost);
		string get_type();
		int get_from();
    	int get_to(); 
		int get_cost();
};

#endif
