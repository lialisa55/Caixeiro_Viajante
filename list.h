typedef struct lista_ LISTA;

typedef struct conexao_ CONEXAO;

LISTA *lista_criar();

void lista_apagar(LISTA *lista);

void lista_remover(LISTA *lista, int indice);

void lista_inserir(LISTA *lista, int destino, int tamanho);

int lista_destino(LISTA *lista, int indice);

int lista_conexao_tamanho(LISTA *lista, int indice)