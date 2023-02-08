/**
 *
 */

#include "../include/AdaptationFunction.h"

/**
 *
 */

AdaptationFunction::AdaptationFunction(int _type, char _from, char _to)
{
	type = _type; 
	from = _from;
	to   = _to;
}

/**
 *
 */

int AdaptationFunction::get_type()
{
	return type;
}

/**
 *
 */

char AdaptationFunction::get_from()
{
	return from;
}

/**
 *
 */

char AdaptationFunction::get_to()
{
	return to;
}