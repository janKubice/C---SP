#include <stdio.h> 
#include <stdlib.h> 

#include "../Headers/graph.h"
#include "../Headers/algorithms.h"

int find(subset *subset, int i)
{
    if (subset[i].parent != i){
        subset[i].parent = find(subset, subset[i].parent);
    }
 
    return subset[i].parent;
}
 

void k_union(subset *subset, int x, int y)
{
    int xroot = find(subset, x);
    int yroot = find(subset, y);
 
    if (subset[xroot].rank < subset[yroot].rank)
        subset[xroot].parent = yroot;
    else if (subset[xroot].rank > subset[yroot].rank)
        subset[yroot].parent = xroot;
 
    else
    {
        subset[yroot].parent = xroot;
        subset[xroot].rank++;
    }
}

void kruskal(graph *graph){
    if (!graph){
        return;
    }

    unsigned int v = graph->vertices;
    edge *result = (edge*)malloc(sizeof(edge)*v); 
    sort_edges(graph->edges_list, graph->edges);

    if (!result){
        printf("Not enough memory - kruskal");
        return;
    }

    int e = 0; 
    int i = 0; 

    subset *subsets = (subset*)malloc(sizeof(subset)*v);
 
    int j;
    for (j = 0; j < v; j++) {
        subsets[j].parent = j;
        subsets[j].rank = 0;
    }
 
    while (e < v - 1 && i < graph->edges) {
        edge next_edge = graph->edges_list[i++];
 
        int x = find(subsets, next_edge.id_src);
        int y = find(subsets, next_edge.id_dest);
 
        if (x != y) {
            result[e++] = next_edge;
            k_union(subsets, x, y);
        }
    }
 

    int minimumCost = 0;
    for (i = 0; i < e; ++i)
    {
        minimumCost += result[i].weight;
    }
    printf("Minimum Cost: %d\n",minimumCost);
    return;
}


void sort_edges(edge *edges, int n){
    int i, j; 
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-i-1; j++){
            if (edges[j].weight > edges[j+1].weight){
                swap(&edges[j], &edges[j+1]);
            } 
        }
    }
}


void swap(edge *edge1, edge *edge2){
    edge temp = *edge1;
    *edge1 = *edge2;
    *edge2 = temp;
}