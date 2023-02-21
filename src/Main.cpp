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

map<string, string> parse_parameters(string params_file)
{
	ifstream file(params_file);
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
			cerr << "error : while reading the parameters file !" << endl;
			exit(EXIT_FAILURE);
		}
	}
	file.close();
	return parameters;
}

/**
 * 
 */

vector<string> *load_infilenames(int argc, char *argv[])
{
	vector<string> *infilenames = new vector<string>(argc-3);
	for (int i = 0; i < argc-3; i++)
	{
		infilenames->at(i) = argv[i+3];
	}
	return infilenames;
}

/**
 * 
 */

int main(int argc, char *argv[])
{   
    map<string, string> parameters = parse_parameters(argv[1]);
	vector<string> *infilenames = load_infilenames(argc,argv);
	string outfilename = argv[2];
	TopologyGenerator *topology_generator = new TopologyGenerator(parameters,outfilename,infilenames);
	delete topology_generator;	
	return EXIT_SUCCESS;
}