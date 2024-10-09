#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "matriz.h"
#define MAX (int)1e9

int min(int a, int b){
    return (a < b) ? a : b;
}
bool not_in(int state, int i){
    return !(state & 1 << i);
}

void combinacoes_helper(LISTA *set, int k, int at, int n, int state){
    if (k == 0){
        lista_pushback(set, state);
    }
    else{
        for (int i = at; i < n; i++){
            state = state | 1 << i;
            combinacoes_helper(set, k - 1, i + 1, n, state);
            state = state & ~(1 << i);
        }
    }
}

LISTA* combinacoes(int k, int n){
    LISTA *set = lista_criar(0);
    combinacoes_helper(set, k, 0, n, 0);
    return set;
    return set;
}

void setup(MATRIZ *memo, MATRIZ *adj, int n, int s, int k){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i != j) matriz_set(adj, i, j, MAX);
            else matriz_set(adj, i, j, 0);
        }
    }
    while (k--){
        int a, b, dist;
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        matriz_set(adj, a, b, dist);
        matriz_set(adj, b, a, dist);
    }
    for (int i = 0; i < n; i++){
        if (s == i) continue;
        matriz_set(memo, i, 1 << s | 1 << i, matriz_get(adj, s, i));
    }
}

void solve(MATRIZ *memo, MATRIZ *adj, int s, int n){
    for (int k = 3; k <= n; k++){
        LISTA *combinations = combinacoes(k, n);
        for (int i = 0; i < lista_tamanho(combinations); i++){
            int combinacao = lista_get_item(combinations, i);
            if (not_in(combinacao, s)) continue;
            for (int proximo = 0; proximo < n; proximo++){
                if (proximo == s || not_in(combinacao, proximo)) continue;
                int quebra = combinacao ^ 1 << proximo;
                int melhor_dist = MAX;
                for (int fim = 0; fim < n; fim++){
                    if (fim == s || not_in(quebra, fim)) continue;
                    int dist = matriz_get(memo, fim, quebra) + matriz_get(adj, fim, proximo);
                    melhor_dist = min(melhor_dist, dist);
                }
                matriz_set(memo, proximo, combinacao, melhor_dist);
            }
        }
        lista_apagar(combinations);
    }
}

int get_best(MATRIZ *memo, MATRIZ *adj, int n, int s){
    int best = MAX;
    for (int i = 0; i < n; i++){
        if (i == s) continue;
        best = min(best, matriz_get(memo, i, (1<<n )-1) + matriz_get(adj, i, s));
    }
    return best;
}

LISTA *get_some_bitches(MATRIZ *memo, MATRIZ *adj, int n, int s){
    LISTA *caminho = lista_criar(n+1);
    int estado = (1<<n )-1;
    int indice_anterior = s;
    for (int i =  n - 1; i >= 1; i--){
        int indice = -1;
        for (int j =  0; j < n; j++){
            if (j == s || not_in(estado, j)) continue;
            if (indice == -1) indice = j;
            int distancia_previa = matriz_get(memo, indice, estado) + matriz_get(adj, indice_anterior, indice);
            int distancia_atual = matriz_get(memo, j, estado) + matriz_get(adj, indice_anterior, j);
            if (distancia_atual < distancia_previa) indice = j;   
        }
        indice_anterior = indice;
        lista_set(caminho, i, indice);
        estado = estado ^ 1 << indice;
    }
    lista_set(caminho, 0, s);
    lista_set(caminho, n, s);
    return caminho;
}

int main(){
    int n, comeco, k;
    scanf("%d %d %d", &n, &comeco, &k);
    comeco--;
    MATRIZ *memo = matriz_criar(n, 1<<n);
    MATRIZ *adj = matriz_criar(n, n);
    setup(memo, adj, n, comeco, k);
    solve(memo, adj, comeco, n);
    int best_dist = get_best(memo, adj, n, comeco);
    LISTA *path = get_some_bitches(memo, adj, n, comeco);
    printf("distancia: %d\n", best_dist);
    for (int i = 0; i < lista_tamanho(path); i++) printf("%d ", lista_get_item(path,i) + 1);
    printf("\n");
    lista_apagar(path);
    matriz_deletar(&memo);
    matriz_deletar(&adj);
}
