#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "Distancias.h"
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

void setup(DISTANCIAS *memo, DISTANCIAS *adj, int n, int s, int k){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i != j) distancias_set(adj, i, j, MAX);
            else distancias_set(adj, i, j, 0);
        }
    }
    while (k--){
        int a, b, dist;
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        distancias_set(adj, a, b, dist);
        distancias_set(adj, b, a, dist);
    }
    for (int i = 0; i < n; i++){
        if (s == i) continue;
        distancias_set(memo, i, 1 << s | 1 << i, distancias_get(adj, s, i));
    }
}

void solve(DISTANCIAS *memo, DISTANCIAS *adj, int s, int n){
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
                    int dist = distancias_get(memo, fim, quebra) + distancias_get(adj, fim, proximo);
                    melhor_dist = min(melhor_dist, dist);
                }
                distancias_set(memo, proximo, combinacao, melhor_dist);
            }
        }
        lista_apagar(combinations);
    }
}

int get_best(DISTANCIAS *memo, DISTANCIAS *adj, int n, int s){
    int best = MAX;
    for (int i = 0; i < n; i++){
        if (i == s) continue;
        best = min(best, distancias_get(memo, i, (1<<n )-1) + distancias_get(adj, i, s));
    }
    return best;
}

LISTA *achar_caminho(DISTANCIAS *memo, DISTANCIAS *adj, int n, int s){
    LISTA *caminho = lista_criar(n+1);
    int estado = (1<<n )-1;
    int indice_anterior = s;
    for (int i =  n - 1; i >= 1; i--){
        int indice = -1;
        for (int j =  0; j < n; j++){
            if (j == s || not_in(estado, j)) continue;
            if (indice == -1) indice = j;
            int distancia_previa = distancias_get(memo, indice, estado) + distancias_get(adj, indice_anterior, indice);
            int distancia_atual = distancias_get(memo, j, estado) + distancias_get(adj, indice_anterior, j);
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
    DISTANCIAS *memo = distancias_criar(n, 1<<n);
    DISTANCIAS *adj = distancias_criar(n, n);
    setup(memo, adj, n, comeco, k);
    solve(memo, adj, comeco, n);
    int best_dist = get_best(memo, adj, n, comeco);
    LISTA *path = achar_caminho(memo, adj, n, comeco);
    for (int i = 0; i < lista_tamanho(path); i++) printf("%d ", lista_get_item(path,i) + 1);
    printf("%d", best_dist);
    lista_apagar(path);
    distancias_deletar(&memo);
    distancias_deletar(&adj);
}
