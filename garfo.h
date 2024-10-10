typedef struct garfo_ GARFO;

GARFO *garfo_criar();

void garfo_apagar(GARFO *garfo);

void garfo_inserir_cidade(GARFO *garfo, int indice);

void garfo_remover_cidade(GARFO *garfo, int indice);

void garfo_inserir_conexao(GARFO *garfo, int indice, int destino, int tamanho);

int garfo_tamanho_conexao(GARFO* garfo, int indice_cidade, int indice_conexao);

int garfo_num_conexoes(GARFO *garfo, int indice_cidade);

int garfo_destino_conexao(GARFO *garfo, int indice_cidade, int indice_conexao);

int garfo_indice_cidade(GARFO *garfo, int indice_cidade);

