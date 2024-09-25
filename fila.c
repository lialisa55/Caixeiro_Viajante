#include <stdio.h>
struct fila_{
    int tamanho;
    int capacidade;
    void** fila;
}
typedef struct fila_ FILA;

FILA* fila_criar(){
    FILA *fila = malloc(sizeof(FILA));
    fila->tamanho = 0;
    fila->capacidade = 8;
    fila->fila = malloc(sizeof(void*) * 8);
}

void fila_empilhar(FILA *fila, void *item){
    if (fila->tamanho = fila->capacidadde)
}