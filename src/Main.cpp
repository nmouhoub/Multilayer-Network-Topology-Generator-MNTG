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

#include <iomanip> 
#include <iostream>

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
	if ( argc < 3 )
	{
		cerr << "Missing parameters on the command line.\n";
		cerr << "Syntax: ./mntg <parameters_file> <output_file> [<input_file_1> <input_file_2> ... <input_file_k>]\n";
		return EXIT_FAILURE;
	}
	else
	{
		map<string, string> parameters = parse_parameters(argv[1]);
		string outfilename = argv[2];
		vector<string> * infilenames = nullptr;
		if ( argc >= 4 )
			infilenames = load_infilenames(argc, argv);
		TopologyGenerator * topology_generator = new TopologyGenerator(parameters, outfilename, infilenames);
		delete topology_generator;
		return EXIT_SUCCESS;
	}
}
