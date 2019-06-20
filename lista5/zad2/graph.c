#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

graph* NEWGraph(){
    graph* temp = malloc(sizeof(graph));
    temp->n = 1;
    temp->m = 1;
    temp->n_size = 32;
    temp->m_size = 32;
    temp->V = malloc(sizeof(vertex)*temp->n_size);
    temp->E = malloc(sizeof(edge)*temp->m_size);
    return temp;
}

void graphAddVertex(graph* graph, int v){
    if (graph->n == graph->n_size -1){
        graph->n_size *= 2;
        graph->V = realloc(graph->V, sizeof(vertex)*graph->n_size);
    }
    graph->V[graph->n].name = v;
    graph->V[graph->n].prev = NULL;
    graph->V[graph->n++].dist = -1;
}

void graphAddEdge(graph* graph, int u, int v, double w){
    if (graph->m == graph->m_size -1){
        graph->m_size *= 2;
        graph->E = realloc(graph->E, sizeof(edge)*graph->m_size);
    }
    graph->E[graph->m].u = u;
    graph->E[graph->m].v = v;
    graph->E[graph->m++].w = w;
}