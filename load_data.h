#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


int check_params(int argc, char *argv[]);

node *load_nodes(FILE *file);

int check_node_file(FILE *file);

edge *load_edges(FILE *file);

int check_edge_file(FILE *file);