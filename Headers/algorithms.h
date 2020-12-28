#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "graph.h"

/* @brief struktura reprezentující podmnožinu pro union-find */
typedef struct _subset {
    int parent;
    int rank;
} subset;

/**
 * @param subset 
 * @param i
 * @brief A utility function to find set of an element i
 */
int find(subset *subset, int i);

/**
 * @param subset 
 * @param x 
 * @param y 
 * @brief sjednotí dva prvky v podmnožině
 */
void k_union(subset *subset, int x, int y);

/**
 * @param graph soubor na zkontrolování
 * @brief kruskalův algoritmus na nalezení minimální kostry grafu
 */
void kruskal(graph *graph);

/**
 * @param edges soubor na zkontrolování
 * @param n
 * @brief pomocí bubble sortu seřadí hrany podle délky
 */
void sort_edges(edge *edges, int n);

/**
 * @param edge1 
 * @param edge2 
 * @brief prohodí dva prvky v paměti
 */
void swap(edge *edge1, edge *edge2);

#endif