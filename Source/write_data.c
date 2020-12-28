#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/graph.h"

void write_edges(char *filename, edge *edges){
    if (!filename || !edges){
        return;
    }

    printf("Creating %s\n",filename);
    FILE *file;
    edge *tmp_edge;
    int count;
 
    file=fopen(filename,"w+");

    if (!file){
        return;
    }
 
    fprintf(file,"WKT,id,nation,cntryname,source,target,clength\n");
    fflush(file);
    int i;
    count = 0;
    tmp_edge = &edges[count];
    while(tmp_edge){
        if (tmp_edge->id > 0){
            fprintf(file,"WKT,%d,%d,%s,%d,%d,%.3f\n", 
                tmp_edge->id, tmp_edge->nation_id, tmp_edge->nation_name, tmp_edge->id_src, tmp_edge->id_dest, tmp_edge->weight);
        }
        fflush(file);
        tmp_edge = &edges[count];
        count++;
    }
    /*TODO nejak to sem nedojede a spadne??*/
    fclose(file);
 
    printf("File created\n",filename);
}