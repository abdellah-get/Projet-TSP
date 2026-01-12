#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "tsp.h"

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Graphe g;
    char filename[100];
    int best_path[MAX];
    float min_cost;
    int start_node;
    int choice;

    printf("\n============================================\n");
    printf("   PROJET TSP - OPTIMISATION DE TOURNEE   \n");
    printf("============================================\n");

    // step 6:
    printf("1. Charger un fichier specifique\n");
    printf("2. Charger 'cities.txt' par defaut\n");
    printf("Votre choix : ");
    if (scanf("%d", &choice) != 1) choice = 2; 
    if (choice == 1) {
        printf("Nom du fichier : ");
        scanf("%s", filename);
        load_graph_from_file(&g, filename);
    } else {
        load_graph_from_file(&g, "cities.txt");
    }

    //  step 3 
    printf("\n[1/3] Calcul des distances reelles (Dijkstra)... ");
    pre_compute_dijkstra(&g);
    printf("Termine.\n");

    printf("\n--- VILLES DISPONIBLES ---\n");
    for(int i=0; i<g.nbv; i++) {
        printf(" %d -> %s\n", i, g.nomville[i]);
    }

    printf("\nEntrez le numero de la ville de depart : ");
    while (scanf("%d", &start_node) != 1 || start_node < 0 || start_node >= g.nbv) {
        printf("Numero invalide. Reessayez : ");
        clear_buffer();
    }

    // step 7
    if (!is_graph_connected(&g, start_node)) {
        printf("\n[ERREUR] Impossible de faire une tournee complete.\n");
        printf("Certaines villes sont inaccessibles (pas de route).\n");
        return 1; 
    }

    //  step 4
    printf("\n[2/3] Recherche du circuit optimal (TSP)... ");
    solve_tsp(&g, start_node, best_path, &min_cost);
    printf("Termine.\n");

    //  step 6
    printf("\n============================================\n");
    printf(" RESULTATS POUR DEPART : %s\n", g.nomville[start_node]);
    printf("============================================\n");
    
    if (min_cost >= INF) {
        printf("Aucun chemin trouve (Graphe deconnecte).\n");
    } else {
        printf("DISTANCE TOTALE : %.2f km\n", min_cost);
        printf("ITINERAIRE      : ");
        
        printf("%s", g.nomville[start_node]);
        for(int i=0; i<g.nbv-1; i++) {
            printf(" -> %s", g.nomville[best_path[i]]);
        }
        printf(" -> %s\n", g.nomville[start_node]);
    }
    printf("============================================\n");

    return 0;
}