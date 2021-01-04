#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/**
 * @brief načte soubor s vrcholy
 * @param file_path cesta k souboru s vrcholy
 * @param n ukazatel na int kam se uloží počet načtených prvků
 * @return pole načtených vrcholů
 */
station *load_nodes(char *file_path, int *n);

/**
 * @param file soubor na zkontrolování
 * @brief zkontroluje zda je soubor s vrcholy ve správném formátu
 * @return 1 - je v pořádku, 0 - není
 */
int check_node_file(FILE *file);

/**
 * @brief získá prvek na pozici pos v řádce, pozice se oddělují pomocí delimiteru 
 * @param line jedna řádka textu
 * @param pos pozice kterou chceme
 * @param delimiter oddělovač podle kterého se bude dělit řádka
 * @return prvek na pozici
 */
char *getfield(char *line, int pos, char *delimiter);

/**
 * @brief načte soubor s hranama a vrátí ukazatel na pole hran
 * @param file_path cesta k souboru
 * @param e ukazatel na int kam se uloží počet načtených prvků
 * @return prvek na pozici
 */
edge *load_edges(char *file_path, int *e);

/**
 * @brief zjistí kolik prvků se v řádce nachází
 * @param line jedna řádka textu
 * @return počet prvků v řádce
 */
int get_param_count(char *line);

/**
 * @brief zjistí kolik parametrů se nachází na řádce, když je méně jak 8 vrátí 8,
 * využívá se pro zjištění toho kde je chybí název státu
 * @param line jedna řádka textu
 * @return počet parametrů
 */
int get_param_count_edges(char *line);

/**
 * @brief zjistí kolik parametrů se nachází na řádce
 * @param line jedna řádka textu
 * @return počet parametrů
 */
int get_real_params(char *line);

/**
 * @brief zkontroluje zda je soubor s hranamy ve správném formátu
 */
int check_edge_file(FILE *file);

float extract_pos(char *line, int pos);

#endif