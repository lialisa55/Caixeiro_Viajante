typedef struct item_ ITEM;
void item_apagar(ITEM *item);
ITEM *item_criar(int chave, void *dado);
int item_get_chave(ITEM *item);
void *item_get_dado(ITEM *item);
