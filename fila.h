#include "item.h"
typedef struct fila_ FILA;
FILA *fila_criar();
void fila_deletar(FILA *fila);
ITEM *fila_topo(FILA *fila);
void fila_empilhar(FILA *fila, ITEM *item);
void fila_desempilhar(FILA *fila);