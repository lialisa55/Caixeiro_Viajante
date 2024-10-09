#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
struct lista_{
    int *start;
    int *end;
    int capacidade;
    int *lista;
};
typedef struct lista_ LISTA;

LISTA *lista_criar(int size){
    LISTA *lista = malloc(sizeof(LISTA));
    lista->capacidade = size > 0 ? size : 1;
    lista->lista = malloc(sizeof(int) * lista->capacidade);
    lista->start = lista->lista;
    lista->end = lista->start + size;
    return lista;
}

void lista_apagar(LISTA *lista){
    free(lista->lista);
    free(lista);
}

int lista_get_item(LISTA *lista, int indice){
    if (indice >= lista_tamanho(lista)){
        printf("index out of bounds\n");
        exit(1);
    }
    return lista->lista[indice];
}

void lista_pushback(LISTA *lista, int valor){
    if (lista_tamanho(lista) == lista->capacidade){
        lista->lista = realloc(lista->lista, lista->capacidade * 2 * sizeof(int));
        int tamanho = lista_tamanho(lista);
        lista->start = lista->lista;
        lista->end = lista->start + tamanho;
        lista->capacidade *= 2;
        if (lista->lista == NULL){
            printf("out of memory for %d\n", lista->capacidade);
            exit(1);
        }
    }
    *lista->end = valor;
    lista->end++;
}

void lista_popback(LISTA *lista){
    lista->end--;
}

void lista_set(LISTA *lista, int indice, int valor){
    if (lista_tamanho(lista) <= indice){
        printf("index %d out of bounds (max %d)\n", indice, lista_tamanho(lista) -1);
        exit(1);
    }
    lista->lista[indice] = valor;
}

int lista_tamanho(LISTA *lista){
    return lista->end - lista->start;
}
