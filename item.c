#include <stdio.h>
struct item_{
    int chave;
    void *dado;
};
typedef struct item_ ITEM;

ITEM *item_criar(int chave, void *dado){
    ITEM *item = malloc(sizeof(ITEM));
    item->chave = chave;
    item->dado = dado;
    return item;
}

int item_get_chave(ITEM *item){
    return item -> chave;
}

void *item_get_dado(ITEM *item){
    return item -> dado;
}

void *item_apagar(ITEM *item){ //fazer ele ser um ponteiro duplo so pra torna-lo nulo me obriga a criar variaveis temporarias desnecessarias
    free(item->dado);
    free(item);
}