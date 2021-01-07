#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include "../Headers/load_data.h"
#include "../Headers/algorithms.h"
#include "../Headers/write_data.h"
#include "../Headers/graph.h"

#define PATH_SIZE 100

int main(int argc, char *argv[])
{
    int i;
    int e_param = 0, v_param = 0;
    char edges_path[PATH_SIZE], nodes_path[PATH_SIZE], e_out_path[PATH_SIZE], m_out_path[PATH_SIZE];
    int m_out = 0, e_out = 0;

    printf("----------LOADING----------\n");

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
        printf("Not all required parameters inserted\n");
        exit(EXIT_FAILURE);
    }

    graph *graph;
    station *nodes;
    edge *edges;
    int e, n;

    /*část s načítáním souboru s vrcholama*/
    FILE *file = fopen(nodes_path, "r");
    if (!file)
    {
        printf("Node file opening failed");
        exit(EXIT_FAILURE);
    }

    if (check_node_file(file))
    {
        printf("Node params checked!\n");
        nodes = load_nodes(nodes_path, &n);
        if (!nodes)
        {
            printf("Nodes loading failure!\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Nodes loaded\n");
        }
    }
    else
    {
        printf("Invalid vertex file.\n");
        exit(1);
    }
    fclose(file);

    /*část s načítámím souboru s hranama*/
    file = fopen(edges_path, "r");
    if (!file)
    {
        printf("Edge file opening failed");
        exit(EXIT_FAILURE);
    }
    if (check_edge_file(file))
    {
        printf("Edge params checked!\n");
        edges = load_edges(edges_path, &e);
        if (!edges)
        {
            printf("Edges loading failure!\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("Edges loaded\n");
        }
    }
    else
    {
        printf("Invalid edge file!\n");
        exit(2);
    }
    

    printf("----------MST----------\n");
    /*-mst přepínač*/
    int kruskal_size;
    if (e_out)
    {
        edge *kruskal_mst;
        printf("Creating graph\n");
        graph = create_graph(nodes, edges, e, n);
        printf("Graph done!\n");

        printf("Kruskal started - mst\n");
        kruskal_mst = kruskal(graph, &kruskal_size);
        /*destroy_edges(graph->edges_list);*/
        printf("Kruskal done - mst\n");

        quick_sort_id(kruskal_mst, 0, kruskal_size);
        write_edges(e_out_path, kruskal_mst, kruskal_size);
        /*destroy_edges(kruskal_mst);
        destroy_graph(graph);*/
    }

    printf("----------MRN----------\n");
    /*-mrn přepínač*/
    if (m_out)
    {
        edge *kruskal_mrn;
        printf("Creating graph -mrn\n");
        graph = create_complete_graph(nodes, n);
        printf("Graph done -mrn!\n");

        printf("Kruskal started - mrn\n");
        
        kruskal_mrn = kruskal(graph, &kruskal_size);
        /*destroy_edges(graph->edges_list);*/
        printf("Kruskal done - mrn\n");

        write_edges_mrn(m_out_path, kruskal_mrn, kruskal_size, nodes);
        /*destroy_edges(kruskal_mst);
        destroy_graph(graph);*/
    }

    printf("----------END----------\n");
    printf("Programm successfuly ended");
    exit(EXIT_SUCCESS);
}