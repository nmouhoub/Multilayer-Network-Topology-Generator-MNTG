/**
 *
 */


#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <igraph.h>
#include <iostream>
#include <utility>
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
		virtual void generate_erdos_renyi_graph(int rand_seed, ERGen type, int n, float p, int directed, int loops) = 0;
		virtual void generate_barabasi_albert_graph(int rand_seed, BAGen type, int n, float p, int m, const igraph_vector_t *outseq, int outpref, float A, int directed, const igraph_t *start_from) = 0;
		virtual Graph get_graph() = 0;
		virtual int get_nb_edges_graph() = 0;
		virtual int get_nb_vertices_graph() = 0;
		virtual set<int> get_vertices_graph() = 0;
		virtual set<pair<int,int>> get_edges_graph() = 0; 
		virtual set<int> get_neighbors(int id) = 0;
		virtual void write_graph(FILE *path) = 0;
};


/**
 *
 */

class GraphGenerator : public IGraphGenerator
{
	private: 
		Graph g;
	public:
		virtual ~GraphGenerator(); 
		virtual void generate_erdos_renyi_graph(int rand_seed, ERGen type, int n, float p, int directed, int loops);
		virtual void generate_barabasi_albert_graph(int rand_seed, BAGen type, int n, float p, int m, const igraph_vector_t *outseq, int outpref, float A, int directed, const igraph_t *start_from);
		virtual Graph get_graph();
		virtual int get_nb_edges_graph();
		virtual int get_nb_vertices_graph();
		virtual set<int> get_vertices_graph();
		virtual set<pair<int,int>> get_edges_graph(); 
		virtual set<int> get_neighbors(int id);
		virtual void write_graph(FILE *path);
};

#endif