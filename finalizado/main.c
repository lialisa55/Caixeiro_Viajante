#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "garfo.h"
#define min(a,b) (a<b ? a:b)
//esta funcao testa recursivamente todo caminho possivel com as conexoes dadas, salvando o melhor caminho em path e a distancia em best
int my_recursion(GARFO *garfo, int visitados[12], int path[12], int cidade, int destino, int dist, int cnt, int n, int *best){
    visitados[cidade] = true;
    for (int i = 0; i < garfo_get_size_connections(garfo, cidade); i++){
        int prev = *best;
        if (garfo_get_connection_destino(garfo,  cidade, i) == destino && cnt == n-1 && dist + garfo_get_connection_dist(garfo, cidade, i) < *best){
            path[cnt+1] = destino;
            *best = dist + garfo_get_connection_dist(garfo, cidade, i);
            break;
        }
        if (!visitados[garfo_get_connection_destino(garfo,  cidade, i)]) my_recursion(garfo, visitados, path, garfo_get_connection_destino(garfo,  cidade, i), destino, dist + garfo_get_connection_dist(garfo, cidade, i), cnt + 1, n, best);
        if (*best < prev){
            path[cnt+1] = garfo_get_connection_destino(garfo,  cidade, i);
        }
    }
    visitados[cidade] = false;
    return *best;
}

int main(){
    int n, comeco, k;
    scanf("%d %d %d", &n, &comeco, &k);
    comeco--;
    GARFO *garfo = garfo_criar(n);
    int a, b, dist;
    while (k--){
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        garfo_add_connection(garfo, a, b, dist);
        garfo_add_connection(garfo, b, a, dist);
    }
    int visitados[12] = {0};
    int path[13] = {comeco, -1, -1, -1, -1, -1, -1, -1, -1};
    int best = 1000000;
    best = my_recursion(garfo, visitados, path,  comeco, comeco, 0, 0, n, &best);
    for (int i = 0; i <= n; i++){
        printf("%d ", path[i]+1);
    }
    printf("%d\n", best);
    garfo_apagar(&garfo);
}
