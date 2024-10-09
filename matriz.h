typedef struct matriz_ MATRIZ;
MATRIZ *matriz_criar(int l, int c);
void matriz_set(MATRIZ *m, int l, int c, int valor);
int matriz_get(MATRIZ *m, int l, int c);
void matriz_deletar(MATRIZ **m);