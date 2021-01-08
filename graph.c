#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <float.h>

#include "graph.h"
#include "algorithms.h"

graph *create_graph(station *node, edge *edges, int edges_count, int node_count)
{
    if (!node || !edges || edges_count <= 0 || node_count <= 0)
    {
        printf("Terminating procces - cant create graph\n");
        exit(EXIT_FAILURE);
    }
    graph *new_graph = (graph *)malloc(sizeof(graph));
    if (!new_graph)
    {
        printf("Not enough memory - graph\n");
        exit(EXIT_FAILURE);
    }

    new_graph->edges = edges_count;
    new_graph->vertices = node_count;
    new_graph->stations_list = node;
    new_graph->edges_list = edges;

    return new_graph;
}

graph *create_complete_graph(station *node, int node_count)
{
    if (!node || node_count <= 0)
    {
        printf("Terminating procces - cant create complete graph\n");
        exit(EXIT_FAILURE);
    }

    int edge_count = (int)((node_count * (node_count - 1)));
    edge *edges = (edge *)malloc(sizeof(edge) * edge_count);
    graph *g = (graph *)malloc(sizeof(graph));

    if (!edges || !g)
    {
        printf("Not enough memory - complete graph\n");
        exit(EXIT_FAILURE);
    }

    int edges_in_g = 0;

    int i, j;
    for (i = 0; i < node_count; i++)
    {
        for (j = 0; j < node_count; j++)
        {
            if (i != j)
            {
                edges[edges_in_g].id = 0;
                edges[edges_in_g].id_src = i;
                edges[edges_in_g].id_dest = j;
                edges[edges_in_g].nation_id = 0;
                edges[edges_in_g].weight = great_circle(node[i].pos_x, node[i].pos_y, node[j].pos_x, node[j].pos_y);
                edges_in_g++;
            }
        }
    }

    g->stations_list = node;
    g->edges_list = (edge *)malloc(sizeof(edge) * edge_count);
    memcpy(g->edges_list, edges, sizeof(edge) * edge_count);
    free(edges);
    edges = NULL;
    g->vertices = node_count;
    g->edges = edges_in_g;
    return g;
}
