#include "lista.h"
#include "item.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct lista_ {
    ITEM **lista;
    int tamanho;
    int capacidade;
};

LISTA *lista_criar(int size){
    LISTA *lista = (LISTA *) malloc(sizeof(LISTA));
    lista->tamanho = 0;
    lista->capacidade = size;
    lista->lista = (LISTA**) malloc(sizeof(ITEM*) *size);
    return(lista);
}

void lista_apagar(LISTA *lista){
    for(int i = 0; i < lista->tamanho; i++){
        item_apagar(lista->lista[i]);
    }
    free(lista);
}

void lista_remover(LISTA *lista, int indice){
    item_apagar(lista->lista[indice]);
    for(int i = indice+1; i < lista->tamanho; i++){
        lista->lista[i-1] = lista->lista[i];
    }
    lista->tamanho--;
}

void lista_push_back(LISTA *lista, ITEM *item){
    if (lista->tamanho == lista->capacidade) realocar(lista, lista->capacidade * 2);
    lista->lista[lista->tamanho++] = item;
}

ITEM *lista_get_item(LISTA *lista, int indice){
    return lista->lista[indice];
}

void realocar(LISTA *lista, int capacidade){
    lista->lista = realloc(lista->lista, sizeof(ITEM*) * capacidade);
}

