#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load_data.h"

#define PATH_SIZE 100

int main(int argc, char *argv[]){
    int i;
    int e_param = 0;
    int v_param = 0;
    char edges[PATH_SIZE], nodes[PATH_SIZE], e_out[PATH_SIZE], m_out[PATH_SIZE];

    if (argc < 2){
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; ++i){
        if (strcmp("-e", argv[i]) == 0){
            strcpy(edges,argv[i+1]);
            e_param = 1;
        }
        else if (strcmp("-v", argv[i]) == 0){
            strcpy(nodes,argv[i+1]);
            v_param = 1;
        }
        else if (strcmp("-mst", argv[i]) == 0){
            strcpy(e_out,argv[i+1]);
        }
        else if (strcmp("-mrn", argv[i]) == 0){
            strcpy(m_out,argv[i+1]);
        }
    }

    if (e_param == 0 || v_param == 0){
        printf("Not all required parameters inserted\n");
        exit(EXIT_FAILURE);
    }
    FILE* file = fopen(nodes, "r");
    
    if (check_node_file(file)){
        printf("Node params checked!");
    }
    else{
        printf("Invalid vertex file.\n");
        exit(1);
    }

    
    exit(EXIT_SUCCESS);
}