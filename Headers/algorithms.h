#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "graph.h"

/* @brief struktura reprezentující podmnožinu pro union-find */
typedef struct _subset
{
    int parent;
    int rank;
} subset;

/**
 * @brief Nalezne kořenový prvek
 * @param subset ukazatel na podmonožiny 
 * @param i index prvku
 */
int find(subset *subset, int i);

/**
 * @brief sjednotí dva prvky v podmnožině
 * @param subset ukazatel na podmonožiny 
 * @param x index prvního prvku
 * @param y index druhého prvku
 */
void k_union(subset *subset, int x, int y);

/**
 * @brief kruskalův algoritmus na nalezení minimální kostry grafu
 * @param graph graf s hranama
 * @param kruskal_size adresa na int kam se uloží počet prvků v nově vytvořeném grafu
 */
edge *kruskal(graph *graph, int *kruskal_size);

/**
 * @brief bere poslední prvek jako pivot, a umístí všechny menší prvky než pivot nalevo 
 * a všechny větší prvky napravo od pivotu
 * @param low index prvního prvku na který můžeme, levá mez
 * @param high index posledního prvku, pravá mez
 */
int divide(edge *edges, int low, int high);

/**
 * @brief bere poslední prvek jako pivot, a umístí všechny menší prvky než pivot nalevo 
 * a všechny větší prvky napravo od pivotu
 * @param low index prvního prvku na který můžeme, levá mez
 * @param high index posledního prvku, pravá mez
 */
int divide_id(edge *edges, int low, int high);

/**
 * @brief bere poslední prvek jako pivot, a umístí všechny menší prvky než pivot nalevo 
 * a všechny větší prvky napravo od pivotu
 * @param low index prvního prvku na který můžeme, levá mez
 * @param high index posledního prvku, pravá mez
 */
int dividen_desc(edge *edges, int low, int high);

/**
 * @brief seřadí prvky s pomocí quick sortu podle délky hran od nejmenších po největší
 * @param low index prvního prvku na který můžeme, levá mez
 * @param high index posledního prvku, pravá mez
 */
void quick_sort(edge *edges, int low, int high);

/**
 * @brief seřadí prvky s pomocí quick sortu podle id od největších po nejmenší
 * @param low index prvního prvku na který můžeme, levá mez
 * @param high index posledního prvku, pravá mez
 */
void quick_sort_id(edge *edges, int low, int high);

/**
 * @brief seřadí prvky s pomocí quick sortu podle délky hran od největší po nejmenší
 * @param low index prvního prvku na který můžeme, levá mez
 * @param high index posledního prvku, pravá mez
 */
void quick_sort_decs(edge *edges, int low, int high);

float great_circle(float x1, float y1, float x2, float y2);

/**
 * @brief prohodí dva prvky
 * @param edge1 první prvek
 * @param edge2 druhý prvek
 */
void swap(edge *edge1, edge *edge2);

void destroy_subsets(subset **subset, int subset_count);

#endif