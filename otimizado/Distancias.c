#include <stdlib.h>
#include <stdio.h>
#include "Distancias.h"
struct distancias_
{
    int linhas, colunas;
    int *distancias;
};

DISTANCIAS *distancias_criar(int l, int c){
    DISTANCIAS *distancias = malloc(sizeof(DISTANCIAS));
    distancias->linhas = l;
    distancias->colunas = c;
    distancias->distancias = malloc(sizeof(int) * l * c);
    return distancias;
}

void distancias_set(DISTANCIAS *m, int l, int c, int valor){
    if (l >= m->linhas || c >= m->colunas){
        printf("matrix index out of bounds\n");
        exit(1);
    }
    int indice = m->colunas * l + c;
    m->distancias[indice] = valor;
}

int distancias_get(DISTANCIAS *m, int l, int c){
    int indice = m->colunas * l + c;
    if (l >= m->linhas || c >= m->colunas){
        printf("matrix index out of bounds\n");
        exit(1);
    }
    return m->distancias[indice];
}

void distancias_deletar(DISTANCIAS **m){
    free((*m)->distancias);
    free(*m);
    *m = NULL;
}
