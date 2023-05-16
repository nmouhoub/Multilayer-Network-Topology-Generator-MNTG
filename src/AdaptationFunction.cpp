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

#include "../include/AdaptationFunction.h"

/**
 *
 */

AdaptationFunction::AdaptationFunction(string _type, int _from, int _to, int _cost)
{
	type = _type; 
	from = _from;
	to   = _to;
	cost = _cost;
}

/**
 *
 */

string AdaptationFunction::get_type()
{
	return type;
}

/**
 *
 */

int AdaptationFunction::get_from()
{
	return from;
}

/**
 *
 */

int AdaptationFunction::get_to()
{
	return to;
}

/**
 *
 */

int AdaptationFunction::get_cost()
{
	return cost;
}