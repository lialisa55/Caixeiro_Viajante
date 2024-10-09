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
    int qtd_conexoes;  
};
typedef struct CIDADE_ CIDADE;

int encontrar_menor_caminho(CIDADE cidades[12], int visitados[12], int path[12], int atual, int destino, int dist, int num_visitadas, int num_cidades, int *best){
    visitados[atual] = true;
    for (int i = 0; i < cidades[atual].qtd_conexoes; i++){
        int prev = *best;
        if (cidades[atual].conexoes[i].no->indice == destino && num_visitadas == num_cidades-1 && dist + cidades[atual].conexoes[i].dist < *best){
            path[num_visitadas+1] = destino;
            *best = dist + cidades[atual].conexoes[i].dist;
            break;
        }
        if (!visitados[cidades[atual].conexoes[i].no->indice]){
            encontrar_menor_caminho(cidades, visitados, path, cidades[atual].conexoes[i].no->indice, destino, dist + cidades[atual].conexoes[i].dist, num_visitadas + 1, num_cidades, best);
        }
        if (*best < prev){
            path[num_visitadas+1] = cidades[atual].conexoes[i].no->indice;
        }
    }
    visitados[atual] = false;
    return *best;
}

int main(void){
    int num_cidades, comeco, num_conexoes;
    scanf("%d %d %d", &num_cidades, &comeco, &num_conexoes);
    comeco--;
    CIDADE *cidades = calloc(num_cidades, sizeof(CIDADE));
    for (int i = 0; i < num_cidades; i++) cidades[i].indice = i;
    int a, b, dist;
    while (num_conexoes--){
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        CONEXAO x = {dist, &cidades[b]}, y = {dist, &cidades[a]};
        cidades[a].conexoes[cidades[a].qtd_conexoes] = x;
        cidades[a].qtd_conexoes++;
        cidades[b].conexoes[cidades[b].qtd_conexoes] = y;
        cidades[b].qtd_conexoes++;
    }
    int visitados[12] = {0};
    int path[13] = {comeco, -1, -1, -1, -1, -1, -1, -1, -1};
    int best = 1000000;
    printf("%d ", encontrar_menor_caminho(cidades, visitados, path,  comeco, comeco, 0, 0, num_cidades, &best));
    for (int i = 0; i <= num_cidades; i++){
        printf("%d ", path[i]+1);
    }
    return 0;
}
