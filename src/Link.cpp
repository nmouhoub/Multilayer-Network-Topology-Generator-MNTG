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

#include "../include/Link.h"

/**
 *
 */

Link::Link(int _src, int _dest, int _cost)
{
	src = _src;
	dest = _dest;
	cost = _cost;
}

/**
 *
 */

int Link::get_src()
{
	return src;
}

/**
 *
 */

int Link::get_dest()
{
	return dest;
}

/**
 *
 */

int Link::get_cost()
{
	return cost;
}

/**
 *
 */

void Link::set_src(int _src)
{
	src = _src;
}

/**
 *
 */

void Link::set_dest(int _dest)
{
	dest = _dest;
}