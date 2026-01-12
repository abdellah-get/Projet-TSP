#include "tsp.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void tsp_permutation(Graphe *g, int current_path[], int l, int r, int start_node, float *min_cost, int best_path[]) {
    if (l == r) {
        float current_cost = 0;
        current_cost += g->mtx[start_node][current_path[0]];
        
        
        for (int i = 0; i < r; i++) {
            current_cost += g->mtx[current_path[i]][current_path[i+1]];
        }
        current_cost += g->mtx[current_path[r]][start_node];
        if (current_cost < *min_cost) {
            *min_cost = current_cost;
            for (int i = 0; i <= r; i++) {
                best_path[i] = current_path[i];
            }
        }
    } else {
        for (int i = l; i <= r; i++) {
            swap(&current_path[l], &current_path[i]);
            tsp_permutation(g, current_path, l+1, r, start_node, min_cost, best_path);
            swap(&current_path[l], &current_path[i]); 
        }
    }
}

void solve_tsp(Graphe *g, int start_node, int best_path[], float *min_cost) {
    int cities_to_visit[MAX];
    int count = 0;


    for (int i = 0; i < g->nbv; i++) {
        if (i != start_node) {
            cities_to_visit[count++] = i;
        }
    }

    *min_cost = INF; 
     
    tsp_permutation(g, cities_to_visit, 0, count-1, start_node, min_cost, best_path);
}