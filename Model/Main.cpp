#include <iomanip>
#include <getopt.h> 
#include <string.h>
#include <stdlib.h>
#include "Generator.hpp"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

using namespace std;

void usage(char *program_name, int status) {
    if (status == EXIT_SUCCESS)
    {
        cout << "Usage: " << program_name << " -g ER -s 1234 -n 50 -m 0 -p 0.20 -a 2 -f 0.10 -o Topologies/topo" << endl
        	 << "Usage: " << program_name << " -g BA -s 14577 -n 50 -m 5 -p 1 -a 2 -f 0.20 -o Topologies/topo" << endl;
	    cout << "    -g: generator type (BA: Barabasi-Albert, ER: Erdos_Renyi)" << endl
			 << "    -s: random seed (non negative)" << endl
	         << "    -n: number of routers of the network (non negative)" << endl
	         << "    -m: number of links for Barabasi-Albert generator (non negative)" << endl
	         << "    -p: connection probability for the graph generator (between 0. and 1.)" << endl
	         << "    -a: number of protocols of the network (non negative)" << endl
	         << "    -f: adaptation function probability for routers (between 0. and 1.)" << endl
	         << "    -o: output directory (ex: Topologies)" << endl
	         << "    -h: help" << endl;
    }
    else
    {
      cerr << "Try '" << program_name << " -h' for help." << endl;
    }
  	exit(status);
}


void parse_args(int argc, char *argv[], char* &gen_type, int &rand_seed, int &nb_routers, int &nb_links, 
	            float &p_gen, int &nb_protocols, float& p_fun, char* &out_file)
{
	extern char *optarg;
	extern int optopt;
  	char c;

  	while ((c = getopt(argc, argv, "g:s:n:m:p:a:f:o:h")) != EOF)
  	{
    	switch (c) 
    	{
	    	case 'h':       /* help */
	      		usage(argv[0], EXIT_SUCCESS);
	      		break;
	      	case 'g':		/* generator type */
	      		gen_type = optarg;
	      		break;
			case 's':		/* random seed */
	      		rand_seed = atoi(optarg);
	      		break;
	    	case 'n':       /* nb routers */
	      		nb_routers = atoi(optarg);
	      		break;
	      	case 'm':		/* nb_links */
	      		nb_links = atoi(optarg);
	      		break;
	      	case 'p':       /* connection probability */
	      		p_gen = atof(optarg);
	      		break;
	    	case 'a':       /* nb protocols */
		     	nb_protocols = atoi(optarg);
		        break;
		    case 'f':		/* function probability */
		    	p_fun = atof(optarg);
		    	break;
			case 'o':  		/* output file */
				out_file = optarg;	
				break;
		    case ':':       /* missing operand */
		      	cerr << argv[0] << ": Option -" << optopt << " requires an operand." << endl;
		      	usage(argv[0], EXIT_FAILURE);
		     	break;

		    case '?':       /* unknown option */
		      	//cerr << argv[0] << ": Unrecognized option -" << optopt << endl;
		      	usage(argv[0], EXIT_FAILURE);
   		}
    }
}

void run_prog_from_parameters(int argc, char *argv[])
{
	// Variables to read the arguments
    int nb_protocols = -1;  
    int nb_routers, nb_links = -1 ;
    float p_gen, p_fun = -1.;
    char *out_file, *gen_type;
	int rand_seed = -1;
    
    // Parse main arguments
    parse_args(argc, argv, gen_type, rand_seed, nb_routers, nb_links, p_gen, nb_protocols, p_fun, out_file);
    if ( (nb_routers <= 0) || (nb_protocols <= 0) || (p_gen < 0. || p_gen > 1.) 
        || ((strcmp(gen_type, "BA") != 0) && (strcmp(gen_type, "ER") != 0)) 
        || (p_fun < 0. || p_fun > 1.) || (rand_seed <= 0) || (out_file[0] == '\0'))
    {
    	usage(argv[0], EXIT_SUCCESS);
    }

    // Create the generator and the network 
	Generator *generator = new Generator(gen_type, rand_seed, nb_routers, nb_links, p_gen, nb_protocols, p_fun);
	
	// Write topology 
	generator->write_topology(out_file);	
	 
    // Delete the generator
	delete generator;	

}

int main(int argc, char *argv[])
{
	switch (argc)
	{
		case 1:
			usage(argv[0], EXIT_FAILURE);
			break;
		default:
			run_prog_from_parameters(argc, argv);
			break;     
	}
	return EXIT_SUCCESS;
}