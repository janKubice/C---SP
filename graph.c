#include <stdio.h> 
#include <stdlib.h> 

#include "graph.h"

graph *create_graph(int vertices, station *nodes){
    if (vertices <= 0){
        return 0;
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
    int i;
    for (i = 0; i < vertices; i++){
        new_graph->list[nodes[i].id].head = &nodes[i];
    }
    new_graph->vertices = vertices;
    printf("%d\n", new_graph->vertices);
    return new_graph;
}

void make_graph(graph *graph, station *nodes, edge *edges, int n, int e){
    if (!graph || !nodes || !edges || n <= 0 || e <= 0){
        return;
    }

    int i, j;

    for (i = 0; i < 100; i++){
        /*printf("%d---%d -> (%d , %d)\n", i,edges[i].id, edges[i].id_src, edges[i].id_dest);*/
        if (edges[i].id == 0){
            continue;
        }
        /*printf("%d -> (%d , %d)\n", edges[i].id, edges[i].id_src, edges[i].id_dest);*/
        add_edge(graph, &edges[i]);
    }
/*
    for (i = 0; i < e; i++){
        if (&edges[i] == NULL){
            continue;
        }
        for (j = 0; j < n; j++){
            if (edges[i].id_src == nodes[j].id){
                edges[i].id_src = nodes[j].id;
            }
            else if (edges[i].id_dest == nodes[j].id){
                edges[i].id_src = nodes[j].id;
            }
        }
        add_edge(graph,&edges[i]);
    }*/

}

void add_edge(graph *graph, edge *edge){
    if (!graph || !edge || edge->id == 0 || edge->id_src == 0 || edge->id_dest == 0){
        return;
    }
    /*printf("%d -> (%d , %d)\n", edge->id, edge->id_src, edge->id_dest);*/
    if (graph->list[edge->id_src].head->first_element == NULL){
        graph->list[edge->id_src].head->first_element = edge;
    }
    else{
        edge->next = graph->list[edge->id_src].head->first_element;
        graph->list[edge->id_src].head->first_element = edge;
    }

/*
    if (graph->list[dest->id].head->first_element == NULL){
        graph->list[dest->id].head->first_element = edge;
    }
    else{
        edge->next = graph->list[dest->id].head->first_element;
        graph->list[dest->id].head->first_element = edge;
    }*/
    
    /*
    edge *newNodeSrc;
    edge *newNodeDest;
    if (graph->list[src->id].head->first_element != NULL){
        edge *tmp = graph->list[src->id].head->first_element;
        newNodeSrc->next = tmp;
        graph->list[src->id].head->next = newNodeSrc;
    }else {
        graph->list[src->id].head->first_element = newNodeSrc;
    }
    */
/*
    if (!newNodeSrc || !newNodeDest){
        return;
    }*/
    /*
    printf("1\n");
    newNodeSrc->next = graph->list[src->id].head;
    newNodeSrc->weight = weight;
    graph->list[src->id].head = newNodeSrc;
    printf("1\n");
    newNodeDest->next = graph->list[dest->id].head;
    newNodeDest->weight = weight;
    graph->list[dest->id].head = newNodeDest;
    printf("1\n");*/

    
}

void print_graph(graph *graph){
    if (!graph){
        return;
    }
    printf("Graph: \n");
    int vert;
    /*TODO nemůžu projíždět jen vertices..id může být víc => prvků taky*/
    for (vert = 1; vert < 200; vert++){
        edge *node = graph->list[vert].head->first_element;

        if (!node){
            continue;
        }

        printf("List of vert: %d\n", graph->list[vert].head->id);
        while (node)
        {
            printf(" -> (e_id: %d - dest: %d) ", node->id, node->id_dest);
            node = node->next;
        }
        printf("\n");
    }
}

