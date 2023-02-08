/**
 *
 */

#ifndef ADAPTATION_FUNCTION_H
#define ADAPTATION_FUNCTION_H

#include <iostream> 
#include <utility>
#include <stack> 

using namespace std;

# define CV  0	// macro of conversion function 
# define EC  1	// macro of encapsulation function
# define DC  2	// macro of decapsulation function

/**
 *
 */

class AdaptationFunction
{
    private:
	    int type; 
		char from; 
		char to; 

    public:		
    	AdaptationFunction(int _type, char _from, char _to);
		int get_type();
		char get_from();
    	char get_to(); 
};

#endif