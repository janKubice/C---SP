#include "point.h"

#ifndef GRAPH_H
#define GRAPH_H

/**
 * @brief
 */
typedef struct _node{
    unsigned int id;
    point position;
    struct _node *neighbours;
} node;

/**
* @brief Struktura uchovávající graf
*/
typedef struct _graph
{
    unsigned int vertices;
    unsigned int edges;
    struct _node *nodes;
} graph;

/**
 * @brief
 */
typedef struct _edge {
    unsigned int id;
    struct _node *node_src;
    struct _node *node_dest;
    float weight;
}edge;

/**
 * @brief
 */
graph *create_graph();

/**
 * @brief
 */
void destroy_graph(graph graph);

/**
 * @brief
 */
void add_edge(graph graph);


#endif