#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/graph.h"

void write_edges(char *filename, edge *edges, int edges_count)
{
    if (!filename || !edges)
    {
        return;
    }

    printf("Creating %s\n", filename);
    FILE *file;
    edge *tmp_edge;
    int count = 0;

    file = fopen(filename, "w+");

    if (!file)
    {
        return;
    }



    fprintf(file, "WKT,id,nation,cntryname,source,target,clength,\n");
    fflush(file);
    int i;

    for (i = 0; i < edges_count; ++i){
        tmp_edge = &edges[i];
        if (tmp_edge->id > 0)
        {
            fprintf(file, "%s))\",%d,%d,%s,%d,%d,%f,\n",
                    tmp_edge->pos, tmp_edge->id, tmp_edge->nation_id, tmp_edge->nation_name, tmp_edge->id_src, tmp_edge->id_dest, tmp_edge->weight);
        }

        if (i % 100 == 0)
        {
            fflush(file);
        }
    }

    fclose(file);
    printf("File created: %s\n", filename);
}

void write_edges_mrn(char *filename, edge *edges, int edges_count, station *nodes)
{
    if (!filename || !edges)
    {
        return;
    }

    printf("Creating %s\n", filename);
    FILE *file;
    edge *tmp_edge;

    file = fopen(filename, "w+");

    if (!file)
    {
        return;
    }

    fprintf(file, "WKT,id,nation,cntryname,source,target,clength,\n");
    fflush(file);
    int i;
    for (i = 0; i < edges_count; ++i){
        tmp_edge = &edges[i];
        if (tmp_edge->id > 0)
        {
             fprintf(file, "\"MULTILINESTRING ((%f %f,%f %f))\",%d,%d,%s,%d,%d,%f,\n",
                    nodes[tmp_edge->id_src].pos_x, nodes[tmp_edge->id_src].pos_y, nodes[tmp_edge->id_dest].pos_x, nodes[tmp_edge->id_dest].pos_y, 
                    tmp_edge->id, tmp_edge->nation_id, tmp_edge->nation_name, tmp_edge->id_src, tmp_edge->id_dest, tmp_edge->weight);
        }

        if (i % 100 == 0)
        {
            fflush(file);
        }
    }

    fclose(file);
    printf("File created: %s\n", filename);
}