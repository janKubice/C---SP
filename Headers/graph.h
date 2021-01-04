#ifndef GRAPH_H
#define GRAPH_H

#define NAME_LENGHT 100
#define COUNTRY_NAME_LENGHT 50
#define WKT_SIZE 12000

/**
 * @brief Struktura reprezentujici vrchol grafu
 */
typedef struct _station
{
    float pos_x;
    float pos_y;
    char name[NAME_LENGHT];
    unsigned int id;
} station;

/**
 * @brief Struktura reprezentujici uzel listu
 * zdroj a cíl uzlu je uchovávaný pouze jako id příslušné hrany
 */
typedef struct _edge
{
    unsigned int id;
    unsigned int nation_id;
    char nation_name[NAME_LENGHT];

    /*string uchovávající MULTILINESTRING*/
    char pos[WKT_SIZE];
    unsigned int id_src;
    unsigned int id_dest;
    float weight;
} edge;

/**
* @brief Struktura uchovavajici graf
* obsahuje počet hran a vrcholů, také obsahuje pole hran a vrcholů
*/
typedef struct _graph
{
    unsigned int vertices;
    unsigned int edges;

    struct _station *stations_list;
    struct _edge *edges_list;
} graph;

/**
 * @brief vytvoří graf reprezentovaný polem hran
 * @param node pole vrcholů
 * @param edges pole hran
 * @param edges_count počet hran
 * @param node_count počet vrcholů
 */
graph *create_graph(station *node, edge *edges, int edges_count, int node_count);

graph *create_complete_graph(station *node,int node_count);

/**
 * @brief uvolní graf z paměti
 * @param graph graf k uvolneni
 */
void destroy_graph(graph **graph);

void destroy_nodes(station **nodes);

void destroy_edges(edge **edges);

#endif