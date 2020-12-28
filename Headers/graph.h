#ifndef GRAPH_H
#define GRAPH_H

#include "point.h"

#define NAME_LENGHT 100
#define COUNTRY_NAME_LENGHT 50

/**
 * @brief Struktura reprezentujici vrchol grafu
 */
typedef struct _station{
    char name[NAME_LENGHT];
    unsigned int id;
    struct _edge *first_element;
}station;

/**
 * @brief Struktura reprezentujici uzel listu
 */
typedef struct _edge{
    unsigned int id;
    unsigned int nation_id;
    char nation_name[NAME_LENGHT];
    struct _edge *next;

    struct _point *points;
    unsigned int id_src;
    unsigned int id_dest;
    float weight;
} edge;

/**
* @brief Struktura uchovavajici list sousednosti
*/
typedef struct _list{
    struct _station *head;
} list;

/**
* @brief Struktura uchovavajici graf
*/
typedef struct _graph
{
    unsigned int vertices;
    unsigned int edges;
    struct _list *list;

    struct _station *stations_list;
    struct _edge *edges_list;
} graph;

/**
 * @brief vytvori prazdny graf se zadanym poctem vrcholu
 * @param vertices pocet vrcholu
 * @param nodes vrcholy grafu
 */
graph *create_graph(int vertices, station *nodes);

/**
 * @brief vytvori graf
 * @param graph graf ktery se ma vytvořit
 * @param nodes vrcholy grafu
 * @param edges hrany grafu
 * @param n pocet vrcholu grafu
 * @param e pocet hran grafu
 */
void make_graph(graph *graph, station *nodes, edge *edges, int n, int e);

/**
 * @brief uvolní graf z paměti
 * @param graph graf k uvolneni
 */
void destroy_graph(graph *graph);

/**
 * @brief přidá do grafu hranu
 * @param graph graf do ktereho se ma pridat
 * @param edge hrana k pridani
 */
void add_edge(graph *graph, edge *edge);

/**
 * @brief Vypise prislusny graf
 * @param graph graf k vypsani
 * @param vert_number kolik vrcholu ma byt vypsano
 */
void print_graph(graph *graph, int vert_number);

#endif