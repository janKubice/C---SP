#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

node *load_nodes(FILE *file);

/**
 * @param file soubor na zkontrolování
 * @brief zkontroluje zda je soubor s vrcholy ve správném formátu
 * @return 1 - je v pořádku, 0 - není
 */
int check_node_file(FILE *file);

/**
 * @param line jedna řádka textu
 * @param pos pozice kterou chceme
 * @brief získá prvek na pozici pos v řádce, pozice se oddělují díky delimiteru (,)
 * @return prvek na pozici
 */
char* getfield(char* line, int pos);

edge *load_edges(FILE *file);

/**
 * @brief zkontroluje zda je soubor s hranamy ve správném formátu
 */
int check_edge_file(FILE *file);