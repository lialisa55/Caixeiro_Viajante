#include <stdlib.h>
#include <stdio.h>
#include "garfo.h"

struct conexao_{
    int dist, destino;
};

struct cidade_{
    int tamanho;
    int indice;
    CONEXAO *conexoes;
};

struct garfo_{
    int tamanho;
    CIDADE *cidades;
};

GARFO* garfo_criar(int n_cidades){
    GARFO *g = malloc(sizeof(GARFO));
    g->tamanho = n_cidades;
    g->cidades = calloc(n_cidades, sizeof(CIDADE));
    for (int i = 0; i < n_cidades; i++){
        g->cidades[i].indice = i;
        g->cidades[i].conexoes = malloc(sizeof(CONEXAO) * n_cidades);
    }
    return g;
}

void garfo_add_connection(GARFO *g, int cidade, int destino, int dist){
    g->cidades[cidade].conexoes[g->cidades[cidade].tamanho].destino = destino;
    g->cidades[cidade].conexoes[g->cidades[cidade].tamanho++].dist = dist;
}

int garfo_get_connection_destino(GARFO *g, int cidade, int indice){
    return g->cidades[cidade].conexoes[indice].destino;
}

int garfo_get_connection_dist(GARFO *g, int cidade, int indice){
    return g->cidades[cidade].conexoes[indice].dist;
}

int garfo_get_size_connections(GARFO *g, int cidade){
    return g->cidades[cidade].tamanho;
}

void garfo_apagar(GARFO **g){
    for (int i = 0; i < (*g)->tamanho; i++){
        free((*g)->cidades[i].conexoes);
    }
    free((*g)->cidades);
    free(*g);
    *g = NULL;
}
