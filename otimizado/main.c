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

void inicializar_distancias(DISTANCIAS *memorizacao, DISTANCIAS *ligacoes, int num_cidades, int comeco, int num_conexoes){
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

void calcular_distancias_minimas(DISTANCIAS *memorizacao, DISTANCIAS *ligacoes, int comeco, int num_cidades){
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

int encontrar_menor_custo(DISTANCIAS *memorizacao, DISTANCIAS *ligacoes, int num_cidades, int comeco){
    int best = MAX;
    for (int i = 0; i < num_cidades; i++){
        if (i == comeco) continue;
        best = min(best, distancias_get(memorizacao, i, (1<<num_cidades )-1) + distancias_get(ligacoes, i, comeco));
    }
    return best;
}

LISTA *reconstruir_melhor_rota(DISTANCIAS *memorizacao, DISTANCIAS *ligacoes, int num_cidades, int comeco){
    LISTA *caminho = lista_criar(num_cidades + 1);
    int estado = (1 << num_cidades) - 1;
    int cidade_anterior = comeco; 

    for (int i = num_cidades - 1; i >= 1; i--) {
        int melhor_cidade = -1;
        for (int cidade_candidata = 0; cidade_candidata < num_cidades; cidade_candidata++) {
            if (cidade_candidata == comeco || not_in(estado, cidade_candidata)) continue;
            
            if (melhor_cidade == -1) {
                melhor_cidade = cidade_candidata;
            }
            
            int distancia_previa = distancias_get(memorizacao, melhor_cidade, estado) + distancias_get(ligacoes, cidade_anterior, melhor_cidade);
            int distancia_atual = distancias_get(memorizacao, cidade_candidata, estado) + distancias_get(ligacoes, cidade_anterior, cidade_candidata);
            
            if (distancia_atual < distancia_previa) {
                melhor_cidade = cidade_candidata; 
            }
        }
        cidade_anterior = melhor_cidade;
        lista_set(caminho, i, melhor_cidade);
        estado = estado ^ 1 << melhor_cidade; 
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
    inicializar_distancias(memorizacao, ligacoes, num_cidades, comeco, num_conexoes);
    calcular_distancias_minimas(memorizacao, ligacoes, comeco, num_cidades);
    int menor_distancia = encontrar_menor_custo(memorizacao, ligacoes, num_cidades, comeco);
    LISTA *menor_rota = reconstruir_melhor_rota(memorizacao, ligacoes, num_cidades, comeco);
    for (int i = 0; i < lista_tamanho(menor_rota); i++){
        printf("%d ", lista_get_item(menor_rota,i) + 1);
    }
    printf("%d", menor_distancia);
    lista_apagar(menor_rota);
    distancias_deletar(&memorizacao);
    distancias_deletar(&ligacoes);
}
