#include "GraphGenerator.hpp"


void GraphGenerator::generate_erdos_renyi_graph(int rand_seed, ERGen type, int n, float p, int directed, int loops)
{

	int error_code = igraph_rng_seed(igraph_rng_default(), rand_seed);
	if ( error_code != 0 )
	{
		cerr << "random seed error" << endl;
	}
	else
	{
		igraph_erdos_renyi_game(&g, type, n, p, directed, loops);
	}
}

void GraphGenerator::generate_barabasi_albert_graph(int rand_seed, BAGen type, int n, float p, int m, const igraph_vector_t *outseq,
			                         int outpref, float A, int directed, const igraph_t *start_from)
{
	int error_code = igraph_rng_seed(igraph_rng_default(), rand_seed);
	if ( error_code != 0 )
	{
		cerr << "random seed error" << endl; 
	}
	else
	{
		igraph_barabasi_game(&g, n, p, m, outseq, outpref, A, directed, type, start_from);
	}
}

Graph GraphGenerator::get_graph()
{
	return g;
}

int GraphGenerator::get_nb_vertices_graph()
{
	return igraph_vcount(&g);
}

int GraphGenerator::get_nb_edges_graph()
{
	return igraph_ecount(&g);
}

set<int> GraphGenerator::get_vertices_graph()
{
	set<int> vertices; 
	VertexIter vit;
    igraph_vit_create(&g, igraph_vss_all() , &vit);
    while (!IGRAPH_VIT_END(vit)) 
    {
        int v_id = IGRAPH_EIT_GET(vit);
        vertices.insert(v_id);
        IGRAPH_VIT_NEXT(vit);
    }
    igraph_vit_destroy(&vit);
    return vertices;
}	

set<pair<int,int>> GraphGenerator::get_edges_graph()
{
	set<pair<int,int>> edges;
	EdgeIter eit;
    igraph_eit_create(&g, igraph_ess_all(IGRAPH_EDGEORDER_FROM), &eit);
    while (!IGRAPH_EIT_END(eit)) 
    {
        int from, to;
        igraph_edge(&g, IGRAPH_EIT_GET(eit), &from, &to);
        edges.insert(make_pair(from, to));
        IGRAPH_EIT_NEXT(eit);
    }
    igraph_eit_destroy(&eit);
    return edges;
}

set<int> GraphGenerator::get_neighbors(int id)
{
	set<int> neighbors;
	VertexIter vit;
	VertexSelect vs;
	igraph_vs_adj(&vs, id, IGRAPH_ALL);
	igraph_vit_create(&g, vs, &vit);
	while (!IGRAPH_VIT_END(vit)) {
	  int v_id = IGRAPH_VIT_GET(vit);
	  neighbors.insert(v_id);
	  IGRAPH_VIT_NEXT(vit);
	}
	igraph_vit_destroy(&vit);
	igraph_vs_destroy(&vs); 
	return neighbors;
}

void GraphGenerator::write_graph(FILE *path)
{
	igraph_write_graph_dot(&g, path);
}

GraphGenerator::~GraphGenerator()
{
	igraph_destroy(&g);
}
