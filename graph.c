#include "graph.h"

void init_graph(Graphe *g, int n) {
    g->nbv = n;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            if (i == j) g->mtx[i][j] = 0;
            else g->mtx[i][j] = INF;
        }
    }
}

void add_edge(Graphe *g, int start, int end, float distance) {
    if (start < g->nbv && end < g->nbv) {
        g->mtx[start][end] = distance;
        g->mtx[end][start] = distance; 
    }
}

void load_graph_from_file(Graphe *g, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("ERREUR: Impossible d'ouvrir %s\n", filename);
        exit(1);
    }
    
    int n;
    fscanf(f, "%d", &n); 
    init_graph(g, n);

  
    for(int i=0; i<n; i++) {
        fscanf(f, "%s", g->nomville[i]);
    }

   
    int u, v;
    float w;
    while(fscanf(f, "%d %d %f", &u, &v, &w) != EOF) {
        add_edge(g, u, v, w);
    }
    fclose(f);
}


void display_graph(Graphe *g) {
    printf("\n--- Matrice des Distances ---\n");
    for(int i=0; i<g->nbv; i++) {
        for(int j=0; j<g->nbv; j++) {
            if(g->mtx[i][j] >= INF) printf("INF\t");
            else printf("%.0f\t", g->mtx[i][j]);
        }
        printf("\n");
    }
}

void pre_compute_dijkstra(Graphe *g) {
    for (int s = 0; s < g->nbv; s++) {
        float dist[MAX];
        int visited[MAX] = {0};
        
        for (int i = 0; i < g->nbv; i++) dist[i] = g->mtx[s][i];
        dist[s] = 0;
        visited[s] = 1;

        for (int count = 0; count < g->nbv - 1; count++) {
            float min = INF;
            int u = -1;

            for (int v = 0; v < g->nbv; v++) {
                if (!visited[v] && dist[v] <= min) {
                    min = dist[v];
                    u = v;
                }
            }

            if (u == -1) break; 
            visited[u] = 1;

            for (int v = 0; v < g->nbv; v++) {
                if (!visited[v] && dist[u] != INF && 
                    dist[u] + g->mtx[u][v] < dist[v]) {
                    dist[v] = dist[u] + g->mtx[u][v];
                }
            }
        }

        for(int i=0; i<g->nbv; i++) {
            g->mtx[s][i] = dist[i];
        }
    }
}

int is_graph_connected(Graphe *g, int start_node) {
    for (int i = 0; i < g->nbv; i++) {
        if (g->mtx[start_node][i] >= INF) {
            printf("ERREUR CRITIQUE: La ville '%s' est inaccessible depuis '%s' !\n", 
                   g->nomville[i], g->nomville[start_node]);
            return 0; 
        }
    }
    return 1; 
}