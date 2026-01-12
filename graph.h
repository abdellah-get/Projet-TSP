
#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50         
#define INF 10000000.0  

typedef struct {
    int nbv;                 
    float mtx[MAX][MAX];    
    char nomville[MAX][50]; 
} Graphe;


void init_graph(Graphe *g, int n);
void add_edge(Graphe *g, int start, int end, float distance);
void display_graph(Graphe *g);
void load_graph_from_file(Graphe *g, const char *filename); 
void pre_compute_dijkstra(Graphe *g); 

#endif
int is_graph_connected(Graphe *g, int start_node);