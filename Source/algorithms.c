#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../Headers/graph.h"
#include "../Headers/algorithms.h"

/*definování PI, nefungovalo mi knihovní PI*/
#define PI acos(-1.0)
#define EARTH_DIA 6371.11

int find(subset *subset, int i)
{
    if (subset[i].parent < 0 || i < 0)
    {
        return -1;
    }
    if (subset[i].parent != i)
    {
        subset[i].parent = find(subset, subset[i].parent);
    }
    return subset[i].parent;
}

void k_union(subset *subset, int x, int y)
{
    if (!subset || x <= 0 || y <= 0)
    {
        return;
    }

    int xroot = find(subset, x);
    int yroot = find(subset, y);

    if (xroot == -1 || yroot == -1)
    {
        return;
    }

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

edge *kruskal(graph *graph, int *kruskal_size)
{
    if (!graph || !kruskal_size)
    {
        return NULL;
    }

    unsigned int v = graph->vertices;
    edge *result = (edge *)malloc(sizeof(edge) * v);
    int size = 0;

    if (!result)
    {
        printf("Not enough memory - kruskal\n");
        return NULL;
    }

    quick_sort(graph->edges_list, 0, graph->edges - 1);

    int e = 0;
    int i = 0;
    int j = 0;

    subset *subsets = (subset *)malloc(sizeof(subset) * v);
    if (!subsets)
    {
        printf("Not enough memory - kruskal - subsets\n");
        return NULL;
    }

    for (j = 0; j < v; j++)
    {
        subsets[j].parent = j;
        subsets[j].rank = 0;
    }

    while (e < v - 1 && i < graph->edges)
    {
        edge next_edge = graph->edges_list[i++];

        int x = find(subsets, next_edge.id_src);
        int y = find(subsets, next_edge.id_dest);

        if (x != y)
        {
            size++;
            memcpy(&result[e++], &next_edge, sizeof(edge));
            k_union(subsets, x, y);
        }
    }
    int a;

    /*destroy_subsets(subsets, v);*/
    *kruskal_size = size;
    return result;
}

void destroy_subsets(subset **subset, int subset_count)
{
    if (!subset || !(*subset) || subset_count <= 0)
    {
        return;
    }

    int i;
    for (i = 0; i < subset_count; i++)
    {
        free(subset[i]);
    }
    free(subset);
    subset = NULL;
}

void swap(edge *edge1, edge *edge2)
{
    if (!edge1 || !edge2)
    {
        return;
    }

    edge temp = *edge1;
    *edge1 = *edge2;
    *edge2 = temp;
}

int divide(edge *edges, int low, int high)
{
    if (!edges)
    {
        return -1;
    }

    float pivot = edges[high].weight;
    int i = (low - 1);
    int j;
    for (j = low; j <= high - 1; j++)
    {

        if (edges[j].weight < pivot)
        {
            i++;
            swap(&edges[i], &edges[j]);
        }
    }
    swap(&edges[i + 1], &edges[high]);
    return (i + 1);
}

int divide_id(edge *edges, int low, int high)
{
    if (!edges)
    {
        return -1;
    }

    int pivot = edges[high].id;
    int i = (low - 1);
    int j;
    for (j = low; j <= high - 1; j++)
    {

        if (edges[j].id > pivot)
        {
            i++;
            swap(&edges[i], &edges[j]);
        }
    }
    swap(&edges[i + 1], &edges[high]);
    return (i + 1);
}

int divide_desc(edge *edges, int low, int high)
{
    if (!edges)
    {
        return -1;
    }

    float pivot = edges[high].weight;
    int i = (low - 1);
    int j;
    for (j = low; j <= high - 1; j++)
    {

        if (edges[j].weight > pivot)
        {
            i++;
            swap(&edges[i], &edges[j]);
        }
    }
    swap(&edges[i + 1], &edges[high]);
    return (i + 1);
}

void quick_sort(edge *edges, int low, int high)
{
    if (low < high)
    {
        int n = divide(edges, low, high);

        if (n == -1)
        {
            return;
        }

        quick_sort(edges, low, n - 1);
        quick_sort(edges, n + 1, high);
    }
}

void quick_sort_id(edge *edges, int low, int high)
{
    if (low < high)
    {
        int n = divide_id(edges, low, high);

        if (n == -1)
        {
            return;
        }

        quick_sort_id(edges, low, n - 1);
        quick_sort_id(edges, n + 1, high);
    }
}

void quick_sort_decs(edge *edges, int low, int high)
{
    if (low < high)
    {
        int n = divide_desc(edges, low, high);

        if (n == -1)
        {
            return;
        }

        quick_sort_decs(edges, low, n - 1);
        quick_sort_decs(edges, n + 1, high);
    }
}

float great_circle(float x1, float y1, float x2, float y2)
{
    float angle = acos((cos(PI/2 - x2) * cos(PI/2 - x1)) + (sin(PI/2 - x1) * sin(PI/2 - x2) * cos(y1 - y2)));
    float distance = angle * (180/PI);
    distance = distance * PI * EARTH_DIA/180;
    return distance;
}
