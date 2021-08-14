#ifndef GRAPHLIBRARYFORPYTHON_H
#define GRAPHLIBRARYFORPYTHON_H
#include "Graph.h"
#include <string>

Graph* create();
void destroy(Graph* graph);
Graph* addVertex(Graph* graph,char* vertex);
Graph* addEdge(Graph* graph,char* source,char* dest);
void disp(Graph* graph);
Graph* graphUnion(Graph* graph_in1,Graph* graph_in2,Graph* graph_out);
Graph* graphIntersection(Graph* graph_in1,Graph* graph_in2,Graph* graph_out);
Graph* graphDifference(Graph* graph_in1,Graph* graph_in2,Graph* graph_out);
Graph* graphProduct(Graph* graph_in1,Graph* graph_in2,Graph* graph_out);
Graph* graphComplement(Graph* graph_in,Graph*  graph_out);


#endif