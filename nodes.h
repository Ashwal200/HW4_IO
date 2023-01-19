#include <stdlib.h>
#include "graph.h"
#ifndef HW3_IO_NODES_H
#define HW3_IO_NODES_H

#endif //HW3_IO_NODES_H


//typedef struct GRAPH_NODE_ {
//    int node_num;
//    pEdge edges;
//    struct GRAPH_NODE_ *next;
//} Node, *pNode;

pNode new_node(int node_number);
void node_free(pNode node);
void add_edge(pNode node, pEdge edge);
