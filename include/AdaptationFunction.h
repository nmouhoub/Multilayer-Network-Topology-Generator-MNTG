/**
 *
 */

#ifndef ADAPTATION_FUNCTION_H
#define ADAPTATION_FUNCTION_H

#include <iostream> 
#include <utility>
#include <stack> 

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