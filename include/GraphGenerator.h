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


#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <string>
#include <vector>
#include <tuple>
#include <set>

#include <igraph/igraph.h>

typedef igraph_t Graph;									//
typedef igraph_vit_t VertexIter;						//
typedef igraph_eit_t EdgeIter; 							//
typedef igraph_vs_t VertexSelect;						//
typedef igraph_erdos_renyi_t ERGen;						//
typedef igraph_barabasi_algorithm_t BAGen;				//

using namespace std;

/**
 *
 */

//class Graph;

class IGraphGenerator
{
	public:
		virtual ~IGraphGenerator() {}
		virtual void generate_erdos_renyi_graph(Graph *g, int rand_seed, int n, float p) = 0;
		virtual void generate_barabasi_albert_graph(Graph *g, int rand_seed, int n, float p, int m) = 0;
		virtual void generate_watts_strogatz_graph(Graph *g, int rand_seed, int n, float p, int k) = 0;
		virtual int get_nb_edges_graph(Graph *g) = 0;
		virtual int get_nb_vertices_graph(Graph *g) = 0;
		virtual vector<int> get_vertices_graph(Graph *g) = 0;
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
		virtual void generate_watts_strogatz_graph(Graph *g, int rand_seed, int n, float p, int k);
		virtual int get_nb_edges_graph(Graph *g);
		virtual int get_nb_vertices_graph(Graph *g);
		virtual vector<int> get_vertices_graph(Graph *g);
		virtual set<tuple<int,int,int>> get_edges_graph(Graph *g); 
		virtual set<int> get_neighbors(Graph *g, int id);
		virtual void delete_vertices(Graph *g, set<int> vertices);
		virtual void read_graph(Graph *g, string infilename);
		virtual void write_graph(Graph *g, string outfilename);
};

#endif
