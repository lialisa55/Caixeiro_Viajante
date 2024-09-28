#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "fila.h"
#define min(a,b) (a<b ? a:b)
//foi usado fila (stack) e item.h
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

struct query_{
    int cidade;
    int rota[12];
    int cnt;
    int dist;
};
typedef struct query_ QUERY;

int my_recursion(CIDADE cidades[12], int visitados[12], int path[12], int cidade, int destino, int dist, int cnt, int n, int *best){
    //if (dp[cidade]) return dp[cidade];
    visitados[cidade] = true;
    printf("%d %d\n", cidade+1, cnt);
    for (int i = 0; i < cidades[cidade].tamanho; i++){
        int prev = *best;
        //printf("%d\n", cidades[cidade].conexoes[i].dist);
        if (cidades[cidade].conexoes[i].no->indice == destino && cnt == n-1 && dist + cidades[cidade].conexoes[i].dist < *best){
            path[cnt+1] = destino;
            *best = dist + cidades[cidade].conexoes[i].dist;
            break;
        }
        if (!visitados[cidades[cidade].conexoes[i].no->indice]) my_recursion(cidades, visitados, path, cidades[cidade].conexoes[i].no->indice, destino, dist + cidades[cidade].conexoes[i].dist, cnt + 1, n, best);
        if (*best < prev){
            path[cnt+1] = cidades[cidade].conexoes[i].no->indice;
            //*best = x;
        }
    }
    //printf("%d %d\n", cidade, best);
    visitados[cidade] = false;
    return *best;
}

int main(){
    int n, comeco, k;
    scanf("%d %d %d", &n, &comeco, &k);
    comeco--;
    CIDADE *cidades = calloc(n, sizeof(CIDADE));
    for (int i = 0; i < n; i++) cidades[i].indice = i;
    int a, b, dist;
    while (k--){
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        CONEXAO x = {dist, &cidades[b]}, y = {dist, &cidades[a]};
        cidades[a].conexoes[cidades[a].tamanho] = x;
        cidades[a].tamanho++;
        cidades[b].conexoes[cidades[b].tamanho] = y;
        cidades[b].tamanho++;
    }
    printf("ola");
    int visitados[12] = {0};
    int path[13] = {comeco, -1, -1, -1, -1, -1, -1, -1, -1};
    int best = 1000000;
    printf("%d ", my_recursion(cidades, visitados, path,  comeco, comeco, 0, 0, n, &best));
    for (int i = 0; i <= n; i++){
        printf("%d ", path[i]+1);
    }
}