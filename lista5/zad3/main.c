#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "graph.h"
#include "priorityQueue.h"

graph* Prim(graph* temp){
    graph* tree = NEWGraph();
    int added[temp->n+1];
    for(int i = 1; i <= temp->n; i++){
        added[i] = 0;
    }

    int s = 1+(rand() % (temp->n-1));
    added[s] = 1;

    queue* queue = NEWQueue(); 

    int adj[temp->n+1][temp->n+1];
    for (int i = 0; i <= temp->n; i++){
        for (int j = 0; j <= temp->n; j++){
            adj[i][j] = -1;
        }
    }
    for(int i = 0; i < temp->m; i++){
        adj[temp->E[i].u][temp->E[i].v]=i;
        adj[temp->E[i].v][temp->E[i].u]=i;
    }

    for(int i = 1; i <= temp->n; i++){
        if(adj[s][i]!=-1){
            queuePUSH(queue, &temp->E[adj[s][i]], temp->E[adj[s][i]].w);
        }
    }

    while (queueIsEmpty(queue) == 0 && tree->n != temp->n){
        if (added[queue->T[0].e->u]==1 && added[queue->T[0].e->v]==1){
            queuePOP(queue);
        } else if (added[queue->T[0].e->u]==1 || added[queue->T[0].e->v]==1) {
            if(added[queue->T[0].e->u]==1){
                int v = queue->T[0].e->v;
                graphAddEdge(tree, queue->T[0].e->u, queue->T[0].e->v, queue->T[0].e->w);
                queuePOP(queue);
                graphAddVertex(tree, v);
                added[v] = 1;
                for(int i = 0; i <= temp->n; i++){
                    if(adj[v][i]!=-1){
                        queuePUSH(queue, &temp->E[adj[v][i]], temp->E[adj[v][i]].w);
                    }
                }
            } else if (added[queue->T[0].e->v]==1) {
                int u = queue->T[0].e->u;
                graphAddEdge(tree, queue->T[0].e->u, queue->T[0].e->v, queue->T[0].e->w);
                queuePOP(queue);
                graphAddVertex(tree, u);
                added[u] = 1;
                for(int i = 0; i <= temp->n; i++){
                    if(adj[u][i]!=-1){
                        queuePUSH(queue, &temp->E[adj[u][i]], temp->E[adj[u][i]].w);
                    }
                }
            } else {
                queuePOP(queue);               
            }
        }
    } 

    return tree;
}

graph* Kruskal(graph* temp){
    graph* tree = NEWGraph();
    int family[temp->n+1];
    for(int i = 1; i <= temp->n; i++){
        family[i] = i;
    }
    queue* queue = NEWQueue();
    for (int i = 0; i<temp->m; i++){
        queuePUSH(queue, &temp->E[i], temp->E[i].w);
    }

    while(tree->m < temp->n-2){
        if (family[queue->T[0].e->u] != family[queue->T[0].e->v]){
            int tempFam = family[queue->T[0].e->u];
            for (int j = 1; j < temp->n; j++) {
                if (family[j] == tempFam) {
                    family[j] = family[queue->T[0].e->v];
                }
            }
            graphAddEdge(tree, queue->T[0].e->u, queue->T[0].e->v, queue->T[0].e->w);
        }
        queuePOP(queue);
    }
    return tree;
}

int main(int argc, char *argv[]){
    graph* temp = NEWGraph();
    graph* tree = NEWGraph();
    
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

    if (argc > 1 && strcmp(argv[1], "-k")==0) {
        tree = Kruskal(temp);
    }else{
        tree = Prim(temp);
    }
    
    double weightsum = 0;
    for (int i = 0; i<tree->m; i++){
        weightsum += tree->E[i].w;
        printf("%i %i %lf\n", tree->E[i].u, tree->E[i].v, tree->E[i].w);
    }
    printf("%f\n", weightsum);
}