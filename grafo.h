#ifndef GRAFO_H
#define GRAFO_H

#include <string.h>
#include <graphviz/cgraph.h>
#include "lista.h"

static const int TEST = 1;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo tem um nome, que é uma "string"

typedef struct grafo *grafo;
typedef struct vertice *vertice;
typedef struct aresta *aresta;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo pode ser direcionado ou não
// 
// o grafo tem um nome, que é uma "string"

struct grafo {
  char* nome;
  long dir;
  lista vert;
  long v;
  long a;
};

//------------------------------------------------------------------------------
// vertice com identificador de tipo=consumidor/produto, nome, vizinhos e grau

struct vertice {
	char* nome;
	char* tipo;
	lista vizinhos;	
	long grau;
};

//------------------------------------------------------------------------------
// aresta com os dois vertices e um peso=recomendações

struct aresta {
	vertice vert;
	long peso;
};

void imprimeGrafo(grafo g);
noh imprimeVert(noh aux,int ares);
noh imprimeAres(noh aux);

grafo criaGrafo(char *nome, long dir, long vert, long ares);
vertice criaVert(char *nome, long grau, char *tipo);
aresta criaAres(vertice v, long peso);

void insereVert(Agraph_t *g, grafo gr);
void constroiViz(Agraph_t *g, grafo gr);

vertice procuraVert(lista l, char *p);
aresta procuraAres(noh aux, vertice v);

Agraph_t* transformaGrafo(grafo g);
noh transformaVert(noh aux, Agraph_t *gr);

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroiGrafo(grafo g);

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input
// 
// devolve o grafo lido,
//         ou 
//         NULL, em caso de erro 

grafo leGrafo(FILE *input);  

//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot.
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 

grafo escreveGrafo(FILE *output, grafo g);

//------------------------------------------------------------------------------
#endif
