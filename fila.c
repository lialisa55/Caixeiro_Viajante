#include <stdio.h>
#include "item.h"
#include "fila.h"
struct fila_{
    int tamanho;
    int capacidade;
    ITEM** fila;
};
typedef struct fila_ FILA;

FILA* fila_criar(){
    FILA *fila = malloc(sizeof(FILA));
    fila->tamanho = 0;
    fila->capacidade = 8;
    fila->fila = malloc(sizeof(ITEM*) * 8);
}

void fila_realocar(FILA *fila, int tamanho){
    fila->fila = realloc(fila->fila, sizeof(ITEM**) * tamanho);
    fila->capacidade = tamanho;
}

void fila_empilhar(FILA *fila, ITEM *item){
    if (fila->tamanho == fila->capacidade) fila_realocar(fila, fila->capacidade * 2);
    fila->fila[fila->tamanho] = item;
    fila->tamanho++;
}

void fila_desempilhar(FILA *fila){
    if (fila->tamanho == 0) return;
    fila->tamanho--;
    item_apagar(fila->fila[fila->tamanho]);
    fila->fila[fila->tamanho] = NULL;
}

void fila_deletar(FILA *fila){
    while (!fila->tamanho) fila_desempilhar(fila);
    free(fila->fila);
    free(fila);
}

ITEM *fila_topo(FILA *fila){
    if (fila -> tamanho == 0) return NULL;
    return fila->fila[fila->tamanho - 1];
}