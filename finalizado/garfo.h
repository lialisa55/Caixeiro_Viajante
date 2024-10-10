typedef struct garfo_ GARFO;
typedef struct conexao_ CONEXAO;
typedef struct cidade_ CIDADE;
GARFO* garfo_criar(int n_cidades);
int garfo_get_connection_destino(GARFO *garfo, int cidade, int indice);
int garfo_get_connection_dist(GARFO *garfo, int cidade, int indice);
int garfo_get_size_connections(GARFO *garfo, int cidade);
void garfo_add_connection(GARFO *garfo, int cidade, int destino, int dist);
void garfo_apagar(GARFO **garfo);
