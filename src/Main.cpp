/**
 *
 */

#include <iomanip>
#include <getopt.h> 
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

void usage(char *program_name, int status) {
    if (status == EXIT_SUCCESS)
    {
        cout << "Usage: " << program_name << " -g ER -s 1234 -n 50 -m 0 -p 0.0 -c 0.20 -a 3 -f 0.10 -w 1 -x 3 -y 2 -z 2 -o output_path/file_name" << endl
        	 << "Usage: " << program_name << " -g BA -s 1857 -n 50 -m 5 -p 1.0 -c 0.00 -a 2 -f 0.20 -w 1 -x 3 -y 2 -z 2 -o output_path/file_name" << endl;
	    cout << "    -g: graph generator type (BA: Barabasi-Albert, ER: Erdos_Renyi)" << endl
			 << "    -s: random seed (non negative)" << endl
	         << "    -n: number of nodes of the network (non negative)" << endl
	         << "    -m: attachment parameter for Barabasi-Albert generator (non negative)" << endl
			 << "    -p: power of attachment for Barabasi-Albert generator (non negative)" << endl
	         << "    -c: connection probability for Erdos_Renyi generator (between 0. and 1.)" << endl
	         << "    -a: number of protocols of the network (non negative)" << endl
	         << "    -f: adaptation function probability for nodes (between 0. and 1.)" << endl
			 << "    -w: cost of classical retransmission function (non negative)" << endl
			 << "    -x: cost of conversion function (non negative)" << endl
			 << "    -y: cost of encapsulation function (non negative)" << endl
			 << "    -z: cost of decapsulation function (non negative)" << endl
	         << "    -o: output directory path and file name (ex., ../data/my_topo)" << endl
	         << "    -h: help" << endl;
    }
    else
    {
      cerr << "Try '" << program_name << " -h' for help." << endl;
    }
  	exit(status);
}


/**
 * 
 */

void parse_args(int argc, char *argv[], char* &gen_type, int &rand_seed, int &nb_nodes, int &m_attach, float &p_attach, float &c_prob, int &nb_protocols, float& f_prob, int &link_cost, int &cv_cost, int &ec_cost, int &dc_cost, char* &out_file)
{
	extern char *optarg;
	extern int optopt;
  	char c;

  	while ((c = getopt(argc, argv, "g:s:n:m:p:c:a:f:w:x:y:z:o:h")) != EOF)
  	{
    	switch (c) 
    	{
	    	case 'h':       // help 
	      		usage(argv[0], EXIT_SUCCESS);
	      		break;
	      	case 'g':		// graph generator type
	      		gen_type = optarg;
	      		break;
			case 's':		// random seed 
	      		rand_seed = atoi(optarg);
	      		break;
	    	case 'n':       // number of nodes 
	      		nb_nodes = atoi(optarg);
	      		break;
	      	case 'm':		// attachement parameter 
	      		m_attach = atoi(optarg);
	      		break;
			case 'p':       // attachement power
	      		p_attach = atof(optarg);
	      		break;
	      	case 'c':       // connection probability 
	      		c_prob = atof(optarg);
	      		break;
	    	case 'a':       // number of protocols 
		     	nb_protocols = atoi(optarg);
		        break;
		    case 'f':		// adaptation function probability 
		    	f_prob = atof(optarg);
		    	break;
			case 'w':		// cost of classical retransmission function
				link_cost = atoi(optarg);
				break;
			case 'x':		// cost of conversion function
				cv_cost = atoi(optarg);
				break;
			case 'y':		// cost of encapsulation function
				ec_cost = atoi(optarg);
				break;
			case 'z':		// cost of decapsulation function
				dc_cost = atoi(optarg);
				break;
			case 'o':  		// output path directory 
				out_file = optarg;	
				break;
		    case ':':       // missing operand 
		      	cerr << argv[0] << ": Option -" << optopt << " requires an operand." << endl;
		      	usage(argv[0], EXIT_FAILURE);
		     	break;

		    case '?':       // unknown option
		      	cerr << argv[0] << ": Unrecognized option -" << optopt << endl;
		      	usage(argv[0], EXIT_FAILURE);
   		}
    }
}


void check_args(char *argv[], char* gen_type, int rand_seed, int nb_nodes, int m_attach, float p_attach, float c_prob, int nb_protocols, float f_prob, int link_cost, int cv_cost, int ec_cost, int dc_cost, char* out_file)
{
	if ( (nb_nodes <= 0) || (nb_protocols <= 0) || (link_cost <= 0) || (cv_cost <= 0) || (ec_cost <= 0) || (dc_cost <= 0) || (rand_seed <= 0) || ((strcmp(gen_type, "BA") != 0) && (strcmp(gen_type, "ER") != 0)) || (f_prob < 0. || f_prob > 1.) || ((c_prob < 0. || c_prob > 1.) && (strcmp(gen_type, "ER") == 0)) || ((m_attach <= 0) && (p_attach <=0.0) && (strcmp(gen_type, "BA") == 0)))
	{
		usage(argv[0], EXIT_SUCCESS);
	}
	
	/*struct stat s;
	if (! (stat(out_file, &s) == 0 && S_ISDIR(s.st_mode)))
	{
		cerr << "error : innvalid output path !" << endl;
		usage(argv[0], EXIT_SUCCESS);
	}*/	
}

/**
 * 
 */

void run_prog_from_parameters(int argc, char *argv[])
{
    int nb_nodes, nb_protocols = -1;  
    int m_attach = -1 ;
	float p_attach;
	int rand_seed = -1;
    float c_prob, f_prob = -1.;
	int link_cost, cv_cost = -1;
	int ec_cost, dc_cost = -1; 
    char *out_file, *gen_type;
    
    parse_args(argc, argv, gen_type, rand_seed, nb_nodes, m_attach ,p_attach, c_prob, nb_protocols, f_prob, link_cost, cv_cost, ec_cost, dc_cost, out_file);
    check_args(argv, gen_type, rand_seed, nb_nodes, m_attach, p_attach, c_prob, nb_protocols, f_prob, link_cost, cv_cost, ec_cost, dc_cost, out_file);
	
	TopologyGenerator *topology_generator = new TopologyGenerator();
	Network* network = topology_generator->generate_mono_random_topology(gen_type, rand_seed, nb_nodes, m_attach, p_attach, c_prob, nb_protocols, f_prob, link_cost, cv_cost, ec_cost, dc_cost);
	topology_generator->write_topology(network, out_file);
	
	delete network;
	delete topology_generator;	
}

/**
 * 
 */

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