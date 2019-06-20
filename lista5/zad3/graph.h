#ifndef GRAPH_H_   /* Include guard */
#define GRAPH_H_

typedef struct vertex {
    int name;
    double dist;
    struct vertex* prev;
} vertex;

typedef struct edge {
    int u, v;
    double w;
} edge;

typedef struct graph {
    int n, m, n_size, m_size;
    edge* E;
    vertex* V;
} graph;

graph* NEWGraph();

void graphAddVertex(graph* graph, int v);

void graphAddEdge(graph* graph, int u, int v, double w);

#endif // GRAPH_H_