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
    int can_add;
    int i, j, e;
    for (i = 0; i < node_count; ++i)
    {
        for (j = 0; j < node_count; ++j)
        {
            can_add = 1;
            for (e = 0; e < edges_in_g; e++)
            {
                if ((edges[e].id_src == i+1 && edges[e].id_dest == j+1) || (edges[e].id_dest == i+1 && edges[e].id_src == j+1))
                {
                    can_add = 0;
                }
            }

            if (i != j && can_add == 1)
            {
                edges[edges_in_g].id = 0;
                edges[edges_in_g].id_src = i + 1;
                edges[edges_in_g].id_dest = j + 1;
                edges[edges_in_g].nation_id = 0;
                edges[edges_in_g].weight = great_circle(node[i].pos_x, node[i].pos_y, node[j].pos_x, node[j].pos_y);
                edges_in_g++;
            }
        }
        g->stations_list = node;
        g->edges_list = edges;
        g->vertices = node_count;
        g->edges = edge_count;

        return g;
    }
}
void destroy_graph(graph **graph)
{
    if (!graph || !(*graph))
    {
        return;
    }

    destroy_edges(&((*graph)->edges_list));
    destroy_nodes(&((*graph)->stations_list));

    free(&graph);
    graph = NULL;
}

void destroy_nodes(station **nodes)
{
    if (!nodes || !(*nodes))
    {
        return;
    }

    int index = 0;
    station *tmp_n = nodes[index];
    while (tmp_n)
    {
        free(&tmp_n);
        tmp_n = NULL;
        index++;
        tmp_n = nodes[index];
    }

    free(nodes);
}

void destroy_edges(edge **edges)
{
    if (!edges || !(*edges))
    {
        return;
    }

    int index = 0;
    edge *tmp_e = edges[index];
    while (tmp_e)
    {
        free(&tmp_e);
        tmp_e = NULL;
        index++;
        tmp_e = edges[index];
    }
    free(edges);
}
