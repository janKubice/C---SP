#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load_data.h"
#define NODES_PARAMS 3
#define EDGES_PARAMS 7

node *load_nodes(FILE *file){

}

int check_node_file(FILE *file){
    if (!file){
        return 0;
    }

    char line[10000];
    int stop_line = 1;
    int param_count = 0;

    while (fgets(line, 10000, file))
    {        
        int i;
        for (i = 1; i <= NODES_PARAMS; i++){
            char *tmp = _strdup(line);
            char *column = getfield(tmp, i);
            if (strcmp("WKT", column) == 0|| strcmp("id", column) == 0 || strcmp("sname", column) == 0){
                param_count++;
            }
        }

        stop_line++;
        if (stop_line == 2){
            break;
        }
    }

    if (param_count == NODES_PARAMS){
        return 1;
    }
    else{
        return 0;
    }
}

char* getfield(char *line, int pos)
{
    char *tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")) {
        if (!--pos)
            return tok;
    }
    return NULL;
}

edge *load_edges(FILE *file){

}

int check_edge_file(FILE *file){

}