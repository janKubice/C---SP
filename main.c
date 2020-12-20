#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_SIZE 100

int main(int argc, char *argv[]){
    int i;
    char edges[PATH_SIZE], nodes[PATH_SIZE], e_out[PATH_SIZE], m_out[PATH_SIZE];

    if (argc < 2){
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; ++i){
        if (strcmp("-e", argv[i]) == 0){
            strcpy(edges,argv[i+1]);
        }
        else if (strcmp("-v", argv[i]) == 0){
            strcpy(nodes,argv[i+1]);
        }
        else if (strcmp("-mst", argv[i]) == 0){
            strcpy(e_out,argv[i+1]);
        }
        else if (strcmp("-mrn", argv[i]) == 0){
            strcpy(m_out,argv[i+1]);
        }
    }

    printf("%s\n%s\n%s\n%s\n", edges, nodes, e_out,m_out);
    exit(EXIT_SUCCESS);
}