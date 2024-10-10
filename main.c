#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "garfo.h"
#define min(a,b) (a<b ? a:b)

//int encontrar_menor_caminho(CIDADE cidades[12], int visitados[12], int path[12], int atual, int destino, int dist, int count, int ncidades, int *best){
int encontrar_menor_caminho(GARFO *garfo, int visitados[12], int path[12], int atual, int destino, int dist, int count, int ncidades, int *best){
    int numconx = garfo_num_conexoes(garfo, atual);
    int destconx = 0;
    int tamconx = 0;
    visitados[atual] = true;
    for (int i = 0; i < numconx; i++){
        destconx = garfo_destino_conexao(garfo, atual, i);
        tamconx = garfo_tamanho_conexao(garfo, atual, i);
        int prev = *best;
        if (destconx == destino && count == ncidades - 1 && dist + tamconx < *best){
            path[count+1] = destino;
            *best = dist + tamconx;
            break;
        }
        if (!visitados[destconx]){
            encontrar_menor_caminho(garfo, visitados, path, destconx, destino, dist + tamconx, count + 1, ncidades, best);
        }
        if (*best < prev){
            path[count+1] = destconx;
        }
    }
    visitados[atual] = false;
    return *best;
}

int main(void){
    int ncidades, comeco, nconexoes;
    scanf("%d %d %d", &ncidades, &comeco, &nconexoes);
    comeco--;
    GARFO *lista_cidades = garfo_criar();
    for (int i = 0; i < ncidades; i++){
        garfo_inserir_cidade(lista_cidades, i);
    }
    int a, b, dist;
    while (nconexoes--){
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        garfo_inserir_conexao(lista_cidades, a, b, dist);
        garfo_inserir_conexao(lista_cidades, b, a, dist);
    }
    int visitados[12] = {0};
    int path[13] = {comeco, -1, -1, -1, -1, -1, -1, -1, -1};
    int best = 1000000;
    printf("%d ", encontrar_menor_caminho(lista_cidades, visitados, path,  comeco, comeco, 0, 0, ncidades, &best));
    for (int i = 0; i <= ncidades; i++){
        printf("%d ", path[i]+1);
    }
    return 0;
}
