#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "load_data.h"
#include "algorithms.h"
#include "write_data.h"
#include "graph.h"

#define PATH_SIZE 100

int main(int argc, char *argv[])
{
    int i;
    int e_param = 0, v_param = 0;
    char edges_path[PATH_SIZE], nodes_path[PATH_SIZE], e_out_path[PATH_SIZE], m_out_path[PATH_SIZE];
    int m_out = 0, e_out = 0;

    /*Ověření parametrů*/
    if (argc < 2)
    {
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    /*Získání parametrů*/
    for (i = 1; i < argc; ++i)
    {
        if (strcmp("-e", argv[i]) == 0)
        {
            strcpy(edges_path, argv[i + 1]);
            e_param = 1;
        }
        else if (strcmp("-v", argv[i]) == 0)
        {
            strcpy(nodes_path, argv[i + 1]);
            v_param = 1;
        }
        else if (strcmp("-mst", argv[i]) == 0)
        {
            strcpy(e_out_path, argv[i + 1]);
            e_out = 1;
        }
        else if (strcmp("-mrn", argv[i]) == 0)
        {
            strcpy(m_out_path, argv[i + 1]);
            m_out = 1;
        }
    }

    if (e_param == 0 || v_param == 0)
    {
        exit(EXIT_FAILURE);
    }

    station *nodes;
    edge *edges;
    int e, n;

    /*část s načítáním souboru s vrcholama*/
    FILE *file = fopen(nodes_path, "r");
    if (!file)
    {
        printf("Invalid vertex file.\n");
        exit(1);
    }

    if (check_node_file(file))
    {
        nodes = load_nodes(nodes_path, &n);
        if (!nodes)
        {
            printf("Invalid vertex file.\n");
            free(nodes);
            fclose(file);
            exit(1);
        }
    }
    else
    {
        printf("Invalid vertex file.\n");
        fclose(file);
        exit(1);
    }
    fclose(file);

    /*část s načítámím souboru s hranama*/
    file = fopen(edges_path, "r");
    if (!file)
    {
        exit(EXIT_FAILURE);
    }
    if (check_edge_file(file))
    {
        edges = load_edges(edges_path, &e);

        if (!edges)
        {
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        printf("Invalid edge file.\n");
        free(nodes);
        fclose(file);
        return 2;
    }
    fclose(file);
    graph *graph;
    /*-mst přepínač*/
    int kruskal_size;
    if (e_out)
    {
        edge *kruskal_mst;
        graph = create_graph(nodes, edges, e, n);

        kruskal_mst = kruskal(graph, &kruskal_size);

        quick_sort_id(kruskal_mst, 0, kruskal_size - 1);
        write_edges(e_out_path, kruskal_mst, kruskal_size);

        free(kruskal_mst);
        free(graph->edges_list);
        free(graph);

    }
    /*-mrn přepínač*/
    if (m_out)
    {

        edge *kruskal_mrn;
        graph = create_complete_graph(nodes, n);

        kruskal_mrn = kruskal(graph, &kruskal_size);

        quick_sort_decs(kruskal_mrn, 0, kruskal_size-1);
        write_edges_mrn(m_out_path, kruskal_mrn, kruskal_size, nodes);

        free(kruskal_mrn);
        free(graph->edges_list);
        free(graph->stations_list);
        free(graph);
    }

    if (!m_out){
        free(nodes);
    }
    
    exit(EXIT_SUCCESS);
}
