#include "AdaptationFunction.hpp"


AdaptationFunction::AdaptationFunction(int _type, char _from, char _to)
{
	type = _type; 
	from = _from;
	to   = _to;
}

int AdaptationFunction::get_type()
{
	return type;
}

char AdaptationFunction::get_from()
{
	return from;
}

char AdaptationFunction::get_to()
{
	return to;
}

void AdaptationFunction::display()
{
	switch (type) 
    {
      case CV: 
      	cout << "Cv " << from << " to " << to << endl;
      	break;
      case EC:  
        cout << "Ec " << from << " in " << to << endl;
      	break;
      case DC:  
        cout << "Dc " << to << " from " << from << endl;
      	break;
      default:
      	cerr << "Invalid type of Adaptation function " << endl; 
      	break;
    }
}