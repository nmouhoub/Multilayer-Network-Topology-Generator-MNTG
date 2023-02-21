/**
 *
 */


#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <igraph.h>
#include <iostream>
#include <utility>
#include <vector>
#include <tuple>
#include <set>

using namespace std;


/**
 *
 */


typedef igraph_t Graph;									//							
typedef igraph_vit_t VertexIter;						//			
typedef igraph_eit_t EdgeIter; 							//		
typedef igraph_vs_t VertexSelect;						//							
typedef igraph_erdos_renyi_t ERGen;						//
typedef igraph_barabasi_algorithm_t BAGen;				//


#define UnDirected IGRAPH_UNDIRECTED 							//
#define NoLoops IGRAPH_NO_LOOPS									//	
#define GNP IGRAPH_ERDOS_RENYI_GNP								//
#define GNM IGRAPH_ERDOS_RENYI_GNM								//
#define BAG IGRAPH_BARABASI_BAG									//
#define PSUMTREE IGRAPH_BARABASI_PSUMTREE						//
#define PSUMTREE_MULTIPLE IGRAPH_BARABASI_PSUMTREE_MULTIPLE		//			


class IGraphGenerator
{
	public:
		virtual ~IGraphGenerator() {}
		virtual void generate_erdos_renyi_graph(Graph *g, int rand_seed, int n, float p) = 0;
		virtual void generate_barabasi_albert_graph(Graph *g, int rand_seed, int n, float p, int m) = 0;
		virtual int get_nb_edges_graph(Graph *g) = 0;
		virtual int get_nb_vertices_graph(Graph *g) = 0;
		virtual set<int> get_vertices_graph(Graph *g) = 0;
		virtual set<tuple<int,int,int>> get_edges_graph(Graph *g) = 0; 
		virtual set<int> get_neighbors(Graph *g, int id) = 0;
		virtual void delete_vertices(Graph *g, set<int> vertices) = 0;
		virtual void read_graph(Graph *g, string infilename) = 0;
		virtual void write_graph(Graph *g, string outfilename) = 0;
};


/**
 *
 */

class GraphGenerator : public IGraphGenerator
{
	public:
		virtual ~GraphGenerator(); 
		virtual void generate_erdos_renyi_graph(Graph *g, int rand_seed, int n, float p);
		virtual void generate_barabasi_albert_graph(Graph *g, int rand_seed, int n, float p, int m);
		virtual int get_nb_edges_graph(Graph *g);
		virtual int get_nb_vertices_graph(Graph *g);
		virtual set<int> get_vertices_graph(Graph *g);
		virtual set<tuple<int,int,int>> get_edges_graph(Graph *g); 
		virtual set<int> get_neighbors(Graph *g, int id);
		virtual void delete_vertices(Graph *g, set<int> vertices);
		virtual void read_graph(Graph *g, string infilename);
		virtual void write_graph(Graph *g, string outfilename);
};

#endif