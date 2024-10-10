#include <stdio.h>
#inum_cidadecomecoclude <comecotdlib.h>
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

void combinacoes_helper(LISTA *set, int num_conexoes, int at, int num_cidades, int state){
    if (num_conexoes == 0){
        lista_pushback(set, state);
    }
    else{
        for (int i = at; i < num_cidades; i++){
            state = state | 1 << i;
            combinacoes_helper(set, num_conexoes - 1, i + 1, num_cidades, state);
            state = state & ~(1 << i);
        }
    }
}

LISTA* combinacoes(int num_conexoes, int num_cidades){
    LISTA *set = lista_criar(0);
    combinacoes_helper(set, num_conexoes, 0, num_cidades, 0);
    return set;
}

void setup(DISTANCIAS *memorizacao, DISTANCIAS *ligacoes, int num_cidades, int comeco, int num_conexoes){
    for (int i = 0; i < num_cidades; i++){
        for (int j = 0; j < num_cidades; j++){
            if (i != j) distancias_set(ligacoes, i, j, MAX);
            else distancias_set(ligacoes, i, j, 0);
        }
    }
    while (num_conexoes--){
        int a, b, dist;
        scanf("%d %d %d", &a, &b, &dist);
        a--; b--;
        distancias_set(ligacoes, a, b, dist);
        distancias_set(ligacoes, b, a, dist);
    }
    for (int i = 0; i < num_cidades; i++){
        if (comeco == i) continue;
        distancias_set(memorizacao, i, 1 << comeco | 1 << i, distancias_get(ligacoes, comeco, i));
    }
}

void solve(DISTANCIAS *memorizacao, DISTANCIAS *ligacoes, int comeco, int num_cidades){
    for (int num_conexoes = 3; num_conexoes <= num_cidades; num_conexoes++){
        LISTA *combinations = combinacoes(num_conexoes, num_cidades);
        for (int i = 0; i < lista_tamanho(combinations); i++){
            int combinacao = lista_get_item(combinations, i);
            if (not_in(combinacao, comeco)) continue;
            for (int proximo = 0; proximo < num_cidades; proximo++){
                if (proximo == comeco || not_in(combinacao, proximo)) continue;
                int quebra = combinacao ^ 1 << proximo;
                int melhor_dist = MAX;
                for (int fim = 0; fim < num_cidades; fim++){
                    if (fim == comeco || not_in(quebra, fim)) continue;
                    int dist = distancias_get(memorizacao, fim, quebra) + distancias_get(ligacoes, fim, proximo);
                    melhor_dist = min(melhor_dist, dist);
                }
                distancias_set(memorizacao, proximo, combinacao, melhor_dist);
            }
        }
        lista_apagar(combinations);
    }
}

int get_best(DISTANCIAS *memorizacao, DISTANCIAS *ligacoes, int num_cidades, int comeco){
    int best = MAX;
    for (int i = 0; i < num_cidades; i++){
        if (i == comeco) continue;
        best = min(best, distancias_get(memorizacao, i, (1<<num_cidades )-1) + distancias_get(ligacoes, i, comeco));
    }
    return best;
}

LISTA *achar_caminho(DISTANCIAS *memorizacao, DISTANCIAS *ligacoes, int num_cidades, int comeco){
    LISTA *caminho = lista_criar(num_cidades+1);
    int estado = (1<<num_cidades )-1;
    int indice_anterior = comeco;
    for (int i =  num_cidades - 1; i >= 1; i--){
        int indice = -1;
        for (int j =  0; j < num_cidades; j++){
            if (j == comeco || not_in(estado, j)) continue;
            if (indice == -1) indice = j;
            int distancia_previa = distancias_get(memorizacao, indice, estado) + distancias_get(ligacoes, indice_anterior, indice);
            int distancia_atual = distancias_get(memorizacao, j, estado) + distancias_get(ligacoes, indice_anterior, j);
            if (distancia_atual < distancia_previa) indice = j;   
        }
        indice_anterior = indice;
        lista_set(caminho, i, indice);
        estado = estado ^ 1 << indice;
    }
    lista_set(caminho, 0, comeco);
    lista_set(caminho, num_cidades, comeco);
    return caminho;
}

int main(void){
    int num_cidades, comeco, num_conexoes;
    scanf("%d %d %d", &num_cidades, &comeco, &num_conexoes);
    comeco--;
    DISTANCIAS *memorizacao = distancias_criar(num_cidades, 1<<num_cidades);
    DISTANCIAS *ligacoes = distancias_criar(num_cidades, num_cidades);
    setup(memorizacao, ligacoes, num_cidades, comeco, num_conexoes);
    solve(memorizacao, ligacoes, comeco, num_cidades);
    int best_dist = get_best(memorizacao, ligacoes, num_cidades, comeco);
    LISTA *path = achar_caminho(memorizacao, ligacoes, num_cidades, comeco);
    for (int i = 0; i < lista_tamanho(path); i++) printf("%d ", lista_get_item(path,i) + 1);
    printf("%d", best_dist);
    lista_apagar(path);
    distancias_deletar(&memorizacao);
    distancias_deletar(&ligacoes);
}
