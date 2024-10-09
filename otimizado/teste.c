#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

int main(){
    MATRIZ *m = matriz_criar(10, 10);
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            matriz_set(m, i, j, i * j);
        }
    }
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            printf("%d ", matriz_get(m, i, j));
        }
        printf("\n");
    }
    matriz_deletar(&m);
}