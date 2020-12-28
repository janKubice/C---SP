#include <stdio.h> 
#include <stdlib.h> 

#include "../Headers/graph.h"

graph *create_graph(int vertices, station *nodes){
    if (vertices <= 0 || !nodes){
        printf("Terminating procces - cant create graph, nodes is NULL");
        exit(EXIT_FAILURE);
    }
   
    graph *new_graph = (graph*)malloc(sizeof(graph));
    if (!new_graph){
        printf("Not enough memory - graph\n");
        return 0;
    }

    new_graph->list = (list*)malloc(sizeof(list) * vertices);
    if (!new_graph->list){
        printf("Not enough memory - list\n");
        return 0;
    }

    /*Podle ID vrcholu přiřadím do listu na index ID vrcholu*/
    int i;
    for (i = 0; i < vertices; i++){
        new_graph->list[nodes[i].id].head = &nodes[i];
    }
    new_graph->vertices = vertices;

    return new_graph;
}

void make_graph(graph *graph, station *nodes, edge *edges, int n, int e){
    if (!graph || !nodes || !edges || n <= 0 || e <= 0){
        printf("Terminating procces - cant create graph");
        exit(EXIT_FAILURE);
    }

    int i, j;

    for (i = 0; i < e; i++){
        if (edges[i].id == 0){
            continue;
        }
        add_edge(graph, &edges[i]);
    }
}

void add_edge(graph *graph, edge *edge){
    if (!graph || !edge || edge->id == 0 || edge->id_src == 0 || edge->id_dest == 0){
        return;
    }
    if (graph->list[edge->id_src].head->first_element == NULL){
        graph->list[edge->id_src].head->first_element = edge;
    }
    else{
        edge->next = graph->list[edge->id_src].head->first_element;
        graph->list[edge->id_src].head->first_element = edge;
    }

    if (graph->list[edge->id_dest].head->first_element == NULL){
        graph->list[edge->id_dest].head->first_element = edge;
    }
    else{
        edge->next = graph->list[edge->id_dest].head->first_element;
        graph->list[edge->id_dest].head->first_element = edge;
    }    
}

void print_graph(graph *graph, int vert_number){
    if (!graph){
        return;
    }
    printf("Graph: \n");
    int vert;
    for (vert = 1; vert < vert_number; vert++){
        edge *node = graph->list[vert].head->first_element;

        if (!node){
            continue;
        }

        printf("List of vert: %d\n", graph->list[vert].head->id);
        while (node->id != -1)
        {
            printf(" -> (e_id: %d - dest: %d) ", node->id, node->id_dest);
            node = node->next;
        }
        printf("\n");
    }
}

