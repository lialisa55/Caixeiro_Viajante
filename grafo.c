#include "lista.h"
struct conexao_{
    int dist;
    int destino;
};
typedef struct conexao_ CONEXAO;

struct cidade_{
    CONEXAO conexoes[12];
    int indice;
    int tamanho;  
};
typedef struct cidade_ CIDADE;
struct grafo_{
    CIDADE *cidades;
    int tamanho;
};
typedef struct grafo_ GRAFO;

GRAFO *grafo_criar(int n_cidades){
    GRAFO *grafo = malloc(sizeof(GRAFO));
    grafo->cidades = malloc(sizeof(CIDADE) * n_cidades);
    grafo->tamanho = n_cidades;
    return grafo;
}

void grafo_adicionar_aresta(GRAFO)