typedef struct distancias_ DISTANCIAS;
DISTANCIAS *distancias_criar(int l, int c);
void distancias_set(DISTANCIAS *m, int l, int c, int valor);
int distancias_get(DISTANCIAS *m, int l, int c);
void distancias_deletar(DISTANCIAS **m);
