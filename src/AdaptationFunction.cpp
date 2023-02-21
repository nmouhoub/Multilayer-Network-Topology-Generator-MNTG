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