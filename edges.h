#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#ifndef HW3_IO_EDGES_H
#define HW3_IO_EDGES_H

#endif //HW3_IO_EDGES_H


//typedef struct edge_ {
//    int weight;
//    pNode endpoint;
//    struct edge_ *next;
//} Edge, *pEdge;


pEdge new_edge(int weight, pNode endpoint);
void free_edge(pEdge edge);

