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

#include <iostream>
#include <utility>

#include "../include/GraphGenerator.h"

/**
 * 
 */

#define UnDirected IGRAPH_UNDIRECTED 							//
#define NoLoops IGRAPH_NO_LOOPS									//
#define GNP IGRAPH_ERDOS_RENYI_GNP								//
#define GNM IGRAPH_ERDOS_RENYI_GNM								//
#define BAG IGRAPH_BARABASI_BAG									//
#define PSUMTREE IGRAPH_BARABASI_PSUMTREE						//
#define PSUMTREE_MULTIPLE IGRAPH_BARABASI_PSUMTREE_MULTIPLE		//

void GraphGenerator::generate_erdos_renyi_graph(Graph *g, int rand_seed, int n, float p)
{
	//igraph_set_attribute_table(&igraph_cattribute_table);
	igraph_i_set_attribute_table(&igraph_cattribute_table);
	int error_code = igraph_rng_seed(igraph_rng_default(), rand_seed);
	if ( error_code != 0 )
	{
		cerr << "random seed error" << endl;
	}
	else
	{
		igraph_erdos_renyi_game(g, GNP, n, p, UnDirected, NoLoops);
	}
}

/**
 * 
 */

void GraphGenerator::generate_barabasi_albert_graph(Graph *g, int rand_seed, int n, float p, int m)
{
	//igraph_set_attribute_table(&igraph_cattribute_table);
	igraph_i_set_attribute_table(&igraph_cattribute_table);
	int error_code = igraph_rng_seed(igraph_rng_default(), rand_seed);
	if ( error_code != 0 )
	{
		cerr << "random seed error" << endl; 
	}
	else
	{
		igraph_barabasi_game(g, n, p, m, 0, 0, 1, UnDirected, PSUMTREE, 0);
	}
}

/**
 * 
 */

void GraphGenerator::generate_watts_strogatz_graph(Graph *g, int rand_seed, int n, float p, int k)
{
	//igraph_set_attribute_table(&igraph_cattribute_table);
	igraph_i_set_attribute_table(&igraph_cattribute_table);
	int error_code = igraph_rng_seed(igraph_rng_default(), rand_seed);
	if ( error_code != 0 )
	{
		cerr << "random seed error" << endl; 
	}
	else
	{
		igraph_watts_strogatz_game(g, 1, n, k, p, NoLoops, false);
	}
}

/**
 * 
 */

int GraphGenerator::get_nb_vertices_graph(Graph *g)
{
	return igraph_vcount(g);
}

/**
 * 
 */

int GraphGenerator::get_nb_edges_graph(Graph *g)
{
	return igraph_ecount(g);
}

/**
 * 
 */

vector<int> GraphGenerator::get_vertices_graph(Graph *g)
{
	vector<int> vertices; 
	VertexIter vit;
    igraph_vit_create(g, igraph_vss_all() , &vit);
    while (!IGRAPH_VIT_END(vit)) 
    {
        int v_id = IGRAPH_EIT_GET(vit);
        vertices.push_back(v_id);
        IGRAPH_VIT_NEXT(vit);
    }
    igraph_vit_destroy(&vit);
	return vertices;
}	

/**
 * 
 */

set<tuple<int,int,int>> GraphGenerator::get_edges_graph(Graph *g)
{
	set<tuple<int,int,int>> edges;
	for (int i = 0; i < igraph_ecount(g); i++) {
		int from = IGRAPH_FROM(g, i);
		int to = IGRAPH_TO(g, i);
		if (igraph_cattribute_has_attr(g,IGRAPH_ATTRIBUTE_EDGE,"weight"))
		{
		/* edge attributes */
			igraph_vector_t gtypes, vtypes, etypes;
			igraph_strvector_t gnames, vnames, enames;

			igraph_vector_init(&gtypes,0);
			igraph_vector_init(&vtypes,0);
			igraph_vector_init(&etypes,0);
			igraph_strvector_init(&gnames,0);
			igraph_strvector_init(&vnames,0);
			igraph_strvector_init(&enames,0);

			igraph_cattribute_list(g,&gnames,&gtypes,&vnames,&vtypes,&enames, &etypes);
			int cost;
			for (int j = 0; j < igraph_strvector_size(&enames); j++) {
				cost = EAN(g, STR(enames, j), i);
			}
			edges.insert(make_tuple(from,to,cost));
		}else 
		{
			edges.insert(make_tuple(from,to,0));
		}
	}
	return edges;
}

/**
 * 
 */

set<int> GraphGenerator::get_neighbors(Graph *g, int id)
{
	set<int> neighbors;
	VertexIter vit;
	VertexSelect vs;
	igraph_vs_adj(&vs, id, IGRAPH_ALL);
	igraph_vit_create(g, vs, &vit);
	while (!IGRAPH_VIT_END(vit)) {
	  int v_id = IGRAPH_VIT_GET(vit);
	  neighbors.insert(v_id);
	  IGRAPH_VIT_NEXT(vit);
	}
	igraph_vit_destroy(&vit);
	igraph_vs_destroy(&vs); 
	return neighbors;
}


/**
 * 
 */

void GraphGenerator::read_graph(Graph *g, string infilename)
{	
	    /* Turn on attribute handling. */
    //igraph_set_attribute_table(&igraph_cattribute_table);
	igraph_i_set_attribute_table(&igraph_cattribute_table);
    FILE *infile = fopen(infilename.c_str(), "r");
    if (infile == 0) 
	{
        exit(EXIT_FAILURE);
    }
    //igraph_read_graph_gml(&g, infile);
	igraph_read_graph_pajek(g,infile);
    fclose(infile);
}

/**
 * 
 */

void GraphGenerator::write_graph(Graph *g, string path)
{
	FILE *file = fopen(path.c_str(), "w");
	igraph_write_graph_dot(g, file);
}

/**
 * 
 */

void GraphGenerator::delete_vertices(Graph *g, set<int> vertices)
{
	for(auto v_id : vertices)
	{
		igraph_delete_vertices(g, igraph_vss_1(v_id));
	}
}

/**
 * 
 */

GraphGenerator::~GraphGenerator() {}
