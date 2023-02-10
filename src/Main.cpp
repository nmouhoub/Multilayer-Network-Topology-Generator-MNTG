/**
 *
 */

#include <iomanip> 
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "../include/TopologyGenerator.h"

using namespace std;

#define EXIT_SUCCESS 0	//
#define EXIT_FAILURE 1	//

/**
 * 
 */

map<string, string> parse_parameters(char *argv[])
{
	ifstream file(argv[1]);
	if ( !file.is_open() )
	{
		cerr << "error : failed to open parameters file !" << endl;
		exit(EXIT_FAILURE);
	}
	map<string, string> parameters;
	string line;
	while ( getline(file, line) )
	{
		if ( !line.find("//") || line.empty() ) 
			continue;
		istringstream iss(line);
		string name, value;
		iss >> name;
		iss >> value;
		parameters[name] = value;
		if ( file.bad() )
		{
			std::cerr << "error : while reading the parameters file !" << endl;
			exit(EXIT_FAILURE);
		}
	}
	file.close();
	return parameters;
}

/**
 * 
 */

int main(int argc, char *argv[])
{   
    map<string, string> parameters = parse_parameters(argv);
	
	TopologyGenerator *topology_generator = new TopologyGenerator();
	Network* network = topology_generator->generate_mono_random_topology(parameters);
	topology_generator->write_topology(network,argv[2]);
	
	delete network;
	delete topology_generator;	

	return EXIT_SUCCESS;
}