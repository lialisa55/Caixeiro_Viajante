#include "item.h"
typedef struct lista_ LISTA;

LISTA *lista_criar();

void lista_apagar(LISTA *lista);

void lista_remover(LISTA *lista, int indice);

ITEM *lista_get_item(LISTA *lista, int indice);

void lista_pushback(LISTA *lista, ITEM *item);