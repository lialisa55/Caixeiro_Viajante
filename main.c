#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "item.h"
#include "fila.h"
#define min(a,b) (a<b ? a:b)
struct conexao_{
    int dist;
    struct CIDADE_ *no;
};
typedef struct conexao_ CONEXAO;

struct CIDADE_{
    CONEXAO conexoes[12];
    int indice;
    int tamanho;  
};
typedef struct CIDADE_ CIDADE;

int encontrar_menor_caminho(CIDADE cidades[12], int visitados[12], int path[12], int atual, int destino, int dist, int cnt, int ncidades, int *best){
    visitados[atual] = true;
    printf("%d %d\n", atual+1, cnt);
    for (int i = 0; i < cidades[atual].tamanho; i++){
        int prev = *best;
        if (cidades[atual].conexoes[i].no->indice == destino && cnt == ncidades-1 && dist + cidades[atual].conexoes[i].dist < *best){
            path[cnt+1] = destino;
            *best = dist + cidades[atual].conexoes[i].dist;
            break;
        }
        if (!visitados[cidades[atual].conexoes[i].no->indice]) encontrar_menor_caminho(cidades, visitados, path, cidades[atual].conexoes[i].no->indice, destino, dist + cidades[atual].conexoes[i].dist, cnt + 1, ncidades, best);
        if (*best < prev){
            path[cnt+1] = cidades[atual].conexoes[i].no->indice;
        }
    }
    visitados[atual] = false;
    return *best;
}

int main(void){
    int ncidades, comeco, nconexoes;
    scanf("%d %d %d", &ncidades, &comeco, &nconexoes);
    comeco--;
    CIDADE *cidades = calloc(ncidades, sizeof(CIDADE));
    for (int i = 0; i < ncidades; i++) cidades[i].indice = i;
    int a, b, dist;
    while (nconexoes--){
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        CONEXAO x = {dist, &cidades[b]}, y = {dist, &cidades[a]};
        cidades[a].conexoes[cidades[a].tamanho] = x;
        cidades[a].tamanho++;
        cidades[b].conexoes[cidades[b].tamanho] = y;
        cidades[b].tamanho++;
    }
    int visitados[12] = {0};
    int path[13] = {comeco, -1, -1, -1, -1, -1, -1, -1, -1};
    int best = 1000000;
    printf("%d ", encontrar_menor_caminho(cidades, visitados, path,  comeco, comeco, 0, 0, ncidades, &best));
    for (int i = 0; i <= ncidades; i++){
        printf("%d ", path[i]+1);
    }
    return 0;
}
