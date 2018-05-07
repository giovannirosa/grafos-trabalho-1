#ifndef GRAFO_H
#define GRAFO_H

#include <string.h>
#include <graphviz/cgraph.h>
#include "lista.h"

static const int TEST = 0;
static const int SIMPLIFICADO = 0;

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

//------------------------------------------------------------------------------
// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes

void imprimeGrafo(grafo g);

//------------------------------------------------------------------------------
// imprime os vertices com seus parâmetros e informações relevantes
// usado para testes

noh imprimeVert(noh aux,int ares);

//------------------------------------------------------------------------------
// imprime as arestas com seus parâmetros e informações relevantes
// usado para testes

noh imprimeAres(noh aux, vertice nome);

//------------------------------------------------------------------------------
// cria um novo grafo alocando memória e definindo suas variáveis

grafo criaGrafo(char *nome, long dir, long vert, long ares);

//------------------------------------------------------------------------------
// cria um novo vertice alocando memória e definindo suas variáveis

vertice criaVert(char *nome, long grau, char *tipo);

//------------------------------------------------------------------------------
// cria uma nova aresta alocando memória e definindo suas variáveis

aresta criaAres(vertice v, long peso);

//------------------------------------------------------------------------------
// insere os vertices ao grafo

void insereVert(Agraph_t *g, grafo gr);

//------------------------------------------------------------------------------
// constrói a vizinhança dos vertices

void constroiViz(Agraph_t *g, grafo gr);

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna o vertice ou NULL se nao encontrar

vertice procuraVert(lista l, char *p);

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna a aresta ou NULL se nao encontrar

aresta procuraAres(noh aux, vertice v);

//------------------------------------------------------------------------------
// transforma o grafo da estrutura grafo para a biblioteca cgraph

Agraph_t* transformaGrafo(grafo g);

//------------------------------------------------------------------------------
// transforma os vertices da estrutura grafo para a biblioteca cgraph

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
