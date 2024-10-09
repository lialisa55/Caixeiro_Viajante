#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
struct matriz_
{
    int linhas, colunas;
    int *matriz;
};

MATRIZ *matriz_criar(int l, int c){
    MATRIZ *matriz = malloc(sizeof(MATRIZ));
    matriz->linhas = l;
    matriz->colunas = c;
    matriz->matriz = malloc(sizeof(int) * l * c);
    return matriz;
}

void matriz_set(MATRIZ *m, int l, int c, int valor){
    if (l >= m->linhas || c >= m->colunas){
        printf("matrix index out of bounds\n");
        exit(1);
    }
    int indice = m->colunas * l + c;
    m->matriz[indice] = valor;
}

int matriz_get(MATRIZ *m, int l, int c){
    int indice = m->colunas * l + c;
    if (l >= m->linhas || c >= m->colunas){
        printf("matrix index out of bounds\n");
        exit(1);
    }
    return m->matriz[indice];
}

void matriz_deletar(MATRIZ **m){
    free((*m)->matriz);
    free(*m);
    *m = NULL;
}