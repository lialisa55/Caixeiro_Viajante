#include "list.h"
#include "garfo.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct cidade_ {
    LISTA *lista;
    int indice;
};

struct garfo_ {
    CIDADE *cidades;
    int inicio;
    int fim;
};

GARFO *garfo_criar(){
    GARFO *garfo = (GARFO *) malloc(sizeof(GARFO));
    garfo->inicio = 0;
    garfo->fim = 0;
    garfo->cidades = NULL;
    return(garfo);
}

void garfo_apagar(GARFO *garfo){
    if(garfo->cidades != NULL){
        for(int i = garfo->fim - 1; i > 0; i--){
            lista_apagar(garfo->cidades[i]->lista);
            garfo->cidades[i]->lista = NULL;
            free(garfo->cidades[i]);
        }
    free(garfo);
    }
}

void garfo_inserir_cidade(GARFO *garfo, int indice){
    garfo->cidades[garfo->fim] = (CIDADE *) malloc(sizeof(CIDADE));
    garfo->cidades[garfo->fim]->indice = indice;
    garfo->cidades[garfo->fim]->lista = lista_criar();
    garfo->fim ++;
    return;
}

void garfo_remover_cidade(GARFO *garfo, int indice){
    for(int i = garfo->inicio; i < garfo->fim; i++){
        if(garfo->cidades[i]->indice == indice){
            lista_apagar(garfo->cidades[i]->lista);
            garfo->cidades[i]->lista = NULL;
            free(garfo->cidades[i]);
            break;
        }
    for(int i = indice; i < garfo->fim; i++){
        garfo->cidades[i] = garfo->cidades[i + 1];
    }
    return;
    }
}

void garfo_inserir_conexao(GARFO *garfo, int indice, int destino, int tamanho){
    for(int i = garfo->inicio; i < garfo->fim; i++){
        if(garfo->cidades[i]->indice == indice){
            lista_inserir(garfo->cidades[i]->lista, destino, tamanho);
            break;
        }
    }
    return;    
}

//int garfo_tamanho_conexao(GARFO *garfo, int indice, int destino){
//    for(int i = garfo->inicio; i < garfo->fim; i++){
//        if(garfo->cidades[i]->indice == indice){
//            return(lista_conexao_tamanho(garfo->cidades[i]->lista, destino));
//        }
//    }
//}

int garfo_tamanho_conexao(GARFO* garfo, int indice_cidade, int indice_conexao){
    return(garfo->cidades[indice_cidade]->lista->conexoes[indice_conexao]->tamanho)
}
int garfo_num_conexoes(GARFO *garfo, int indice_cidade){
    return(garfo->cidades[indice_cidade]->lista->num_conexoes);
}

int garfo_destino_conexao(GARFO *garfo, int indice_cidade, int indice_conexao){
    return(garfo->cidades[indice_cidade]->lista->conexoes[indice_conexao]->destino);
}

int garfo_indice_cidade(GARFO *garfo, int indice_cidade){
    return(garfo->cidades[indice_cidade]->indice);
}