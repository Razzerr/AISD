#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "graph.h"
#include "priorityQueue.h"

void Dijkstra(graph* graph, int s){
    graph->V[s].dist = 0;
    queue* queue = NEWQueue(); 
    for(int i = 1; i<graph->n; i++){
        if (i!=s) graph->V[i].dist = INFINITY;
        graph->V[i].prev = NULL;
        queuePUSH(queue, &graph->V[i], graph->V[i].dist);
    }

    while (queueIsEmpty(queue) == 0){
        vertex* u = queue->T[0].v;
        queuePOP(queue);
        for (int i = 0; i < graph->m; i++){
            if (graph->E[i].u == u->name){
                double alt = u->dist + graph->E[i].w;
                //printf("alt: %lf || dist: %lf\n", alt, graph->V[graph->E[i].v].dist);
                if (alt < graph->V[graph->E[i].v].dist){
                    graph->V[graph->E[i].v].dist = alt;
                    graph->V[graph->E[i].v].prev = u;
                    queueChangePriority(queue, &graph->V[graph->E[i].v]);
                }
            }
        }
    }
}

int main(){
    graph* temp = NEWGraph();
    
    int n, m, s;
    scanf("%i", &n);
    for (int i = 1; i <=n; i++){
        graphAddVertex(temp, i);
    }
    scanf("%i", &m);
    for (int i = 0; i < m; i++) {
        int u = 0, v = 0;
        double w = 0;
        scanf("%i", &u); scanf("%i", &v); scanf("%lf", &w);
        graphAddEdge(temp, u, v, w);
    }
    scanf("%i", &s);
    clock_t start, end;
    start = clock();
    Dijkstra(temp, s);
    end = clock();
    for (int i = 1; i<=n; i++){
        printf("%i %lf\n", i, temp->V[i].dist);
        vertex* tp = &temp->V[i];
        while (tp->prev){
            fprintf(stderr, "(%i, %lf)<-", tp->name, tp->dist);
            tp = tp->prev;
        }
        fprintf(stderr, "(%i, %lf)\n", tp->name, tp->dist);
    }
    fprintf(stderr, "Dijkstra exec time: %f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
}