#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "garfo.h"
#define min(a,b) (a<b ? a:b)

int encontrar_menor_caminho(GARFO *garfo, int visitados[12], int path[12], int atual, int destino, int dist, int num_visitadas, int num_cidades, int *best){
    visitados[atual] = true;
    for (int i = 0; i < garfo_get_size_connections(garfo, atual); i++){
        int prev = *best;
        if (garfo_get_connection_destino(garfo, atual, i) == destino && num_visitadas == num_cidades-1 && dist + garfo_get_connection_dist(garfo, atual, i) < *best){
            path[num_visitadas+1] = destino;
            *best = dist + garfo_get_connection_dist(garfo, atual, i);
            break;
        }
        if (!visitados[garfo_get_connection_destino(garfo,  atual, i)]){
            encontrar_menor_caminho(garfo, visitados, path, garfo_get_connection_destino(garfo,  atual, i), destino, dist + garfo_get_connection_dist(garfo, atual, i), num_visitadas + 1, num_cidades, best);
        }
        if (*best < prev){
            path[num_visitadas+1] = garfo_get_connection_destino(garfo,  atual, i);
        }
    }
    visitados[atual] = false;
    return *best;
}

int main(){
    int num_cidades, comeco, num_conexoes;
    scanf("%d %d %d", &num_cidades, &comeco, &num_conexoes);
    comeco--;
    GARFO *garfo = garfo_criar(num_cidades);
    int a, b, dist;
    while (num_conexoes--){
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        garfo_add_connection(garfo, a, b, dist);
        garfo_add_connection(garfo, b, a, dist);
    }
    int visitados[12] = {0};
    int path[13] = {comeco, -1, -1, -1, -1, -1, -1, -1, -1};
    int best = 1000000;
    best = encontrar_menor_caminho(garfo, visitados, path,  comeco, comeco, 0, 0, num_cidades, &best);
    for (int i = 0; i <= num_cidades; i++){
        printf("%d ", path[i]+1);
    }
    printf("%d\num_cidades", best);
    garfo_apagar(&garfo);
}
