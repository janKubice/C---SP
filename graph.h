#include "point.h"

#ifndef GRAPH_H
#define GRAPH_H

#define NODE_NAME_LENGHT 100
#define COUNTRY_NAME_LENGHT 50

typedef struct _station{
    char name[NODE_NAME_LENGHT];
    unsigned int id;
    struct _edge *first_element;
}station;

/**
 * @brief Struktura reprezentující uzel listu
 */
typedef struct _edge{
    unsigned int id;
    struct _edge *next;

    unsigned int id_src;
    unsigned int id_dest;
    float weight;
} edge;

/**
* @brief Struktura uchovávající list sousednosti
*/
typedef struct _list{
    struct _station *head;
} list;

/**
* @brief Struktura uchovávající graf
*/
typedef struct _graph
{
    unsigned int vertices;
    struct _list *list;
} graph;

/**
 * @brief vytvoří graf se zadaným počtem vrcholů
 */
graph *create_graph(int vertices, station *nodes);

void make_graph(graph *graph, station *nodes, edge *edges, int n, int e);

/**
 * @brief uvolní graf z paměti
 */
void destroy_graph(graph *graph);

/**
 * @brief přidá do grafi hranu
 */
void add_edge(graph *graph, edge *edge);

void print_graph(graph *graph);

#endif