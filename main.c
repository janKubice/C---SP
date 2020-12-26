#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "load_data.h"

#define PATH_SIZE 100

int main(int argc, char *argv[]){
    int i;
    int e_param = 0;
    int v_param = 0;
    char edges_path[PATH_SIZE], nodes_path[PATH_SIZE], e_out_path[PATH_SIZE], m_out_path[PATH_SIZE];

    if (argc < 2){
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; ++i){
        if (strcmp("-e", argv[i]) == 0){
            strcpy(edges_path,argv[i+1]);
            e_param = 1;
        }
        else if (strcmp("-v", argv[i]) == 0){
            strcpy(nodes_path,argv[i+1]);
            v_param = 1;
        }
        else if (strcmp("-mst", argv[i]) == 0){
            strcpy(e_out_path,argv[i+1]);
        }
        else if (strcmp("-mrn", argv[i]) == 0){
            strcpy(m_out_path,argv[i+1]);
        }
    }

    if (e_param == 0 || v_param == 0){
        printf("Not all required parameters inserted\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(nodes_path, "r");
    graph *graph;
    station *nodes;
    edge *edges;
    int e,n;
    
   if (check_node_file(file)){
        printf("Node params checked!\n");
        nodes = load_nodes(nodes_path,&n);
        if (!nodes){
            printf("Nodes loading failure!\n");
            exit(EXIT_FAILURE);
        }
        else{
            printf("Nodes loaded\n");
        }
    }
    else{
        printf("Invalid vertex file.\n");
        exit(1);
    }
    fclose(file);

    file = fopen(edges_path, "r");
    if (check_edge_file(file)){
        printf("Edge params checked!\n");
        edges = load_edges(edges_path,&e);
        if (!edges){
            printf("Edges loading failure!\n");
            exit(EXIT_FAILURE);
        }else{
             printf("Edges loaded\n");
        }
    }else{
        printf("Invalid edge file!\n");
        exit(2);
    }
    printf("Creating graph");
    graph = create_graph(n, nodes);
    printf("Making graph\n");
    make_graph(graph, nodes,edges, n,e);
    printf("Graph done!\n");
    print_graph(graph);
    exit(EXIT_SUCCESS);
}