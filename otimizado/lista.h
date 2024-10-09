
typedef struct lista_ LISTA;

LISTA *lista_criar(int size);

void lista_apagar(LISTA *lista);

void lista_popback(LISTA *lista);

int lista_get_item(LISTA *lista, int indice);

void lista_pushback(LISTA *lista, int fuckm);

void lista_set(LISTA *lista, int indice, int num);

int lista_tamanho(LISTA *lista);
