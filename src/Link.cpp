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