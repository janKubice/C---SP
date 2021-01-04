#ifndef WRITE_DATA_H
#define WRITE_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

/**
 * @brief zapíše hrany do souboru
 * @param filename název souboru kam se má zapisovat
 * @param edges pole hran k zapsání
 */
void write_edges(char *filename, edge *edges, int edges_count);

/**
 * @brief zapíše hrany do souboru, využití při vstupním parametrů mrn
 * @param filename název souboru kam se má zapisovat
 * @param edges pole hran k zapsání
 */
void write_edges_mrn(char *filename, edge *edges, int edges_count, station *nodes);

#endif