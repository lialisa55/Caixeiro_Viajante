#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct conexao_ {
    int destino;
    int tamanho;
};

struct lista_ {
    CONEXAO *conexoes;
    int num_conexoes;
    int fim;
};

LISTA *lista_criar(){
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));
    lista->conexoes = NULL;
    lista->num_conexoes = 0;
    lista->fim = 0;
    return(lista);
}

void lista_apagar(LISTA *lista){
    if(lista->conexoes != NULL){
        lista->fim --;
        for(i = garfo->fim; i > 0; i--){
            lista->conexoes[i] = NULL;
            free(lista->conexoes[i]);
        }
    }
    free(lista);
    return;
}

void lista_remover(LISTA *lista, int destino){
    lista->fim --;
    lista->conexoes[indice] = NULL;
    free(lista->conexoes[indice]);
    for(int i = indice; i < lista->fim; i++){
        lista->conexoes[i] = lista->conexoes[i+1];
    }
    lista->num_conexoes -= 1;
    return;
}

void lista_inserir(LISTA *lista, int destino, int tamanho){
    lista->conexoes[lista->fim] = (CONEXAO *) malloc(sizeof(CONEXAO));
    lista->conexoes[lista->fim]->destino = destino;
    lista->conexoes[lista->fim]->tamanho = tamanho;
    lista->fim ++;
    lista->num_conexoes += 1;
    return;
}

int lista_conexao_tamanho(LISTA *lista, int destino){
    for(int i = 0; i < lista->fim; i++){
        if(indice == lista->conexoes[i]->destino){
            return(lista->conexoes[i]->tamanho);
        }
    }
}

