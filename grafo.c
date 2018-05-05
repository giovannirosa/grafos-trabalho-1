#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "lista.h"
#include <graphviz/cgraph.h>

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo pode ser direcionado ou não
// 
// o grafo tem um nome, que é uma "string"

struct grafo {
  char* nome;
  int dir;
  int peso;
  lista vert;
  int v;
  int a;
};

//------------------------------------------------------------------------------
// vertice com identificador de tipo=consumidor/produto, nome, vizinhos e grau

struct vertice {
	char* nome;
	char tipo;
	lista vizinhos;	
	long grau;
};

//------------------------------------------------------------------------------
// aresta com os dois vertices e um peso = recomendações

struct aresta {
	vertice vert;
	long peso;
};

//------------------------------------------------------------------------------
// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes

void imprimeGrafo(grafo g) {
  printf("Nome: %s | Dir: %d | Vert: %d | Arest: %d\n", g->nome, g->dir, g->v, g->a);
}

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroi_grafo(grafo g) {

  return 0;
}

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input
// 
// devolve o grafo lido,
//         ou 
//         NULL, em caso de erro 

grafo le_grafo(FILE *input) {
  printf("Lendo grafo do arquivo...\n");
  Agraph_t *g = NULL;

  grafo gr = malloc(sizeof(struct grafo));
	printf("Aloca grafo\n");
	g = agread(input, NULL);
	gr->nome = agnameof(g);
	gr->dir = agisdirected(g);	 
	gr->v = agnnodes(g);
	gr->a = agnedges(g);
	insereVert(g,gr);
  imprimeGrafo(gr);

	//adiciona todos os vertices lidos do arquivo dot
	//para a nossa estrutura
	// adiciona_vertices(g, grafo);

	//adiciona todas as arestas de entrada e saida de cada vertice
	//em suas respectivas listas
	// graf->ponderado = adiciona_arestas(g, grafo);

	agclose(g);

  printf("Grafo lido.\n");

	return gr;
}

//------------------------------------------------------------------------------
// insere os vertices ao grafo

void insereVert(Agraph_t *g, grafo gr) {
	Agnode_t *v = NULL;
	vertice vert = NULL;
	gr->vert = iniciaLista();

	printf("------------------------------------------\n");
  for(v = agfstnode(g); v; v = agnxtnode(g,v)){	        	
      vert = malloc(sizeof(struct vertice));
			vert->nome = agnameof(v);
			vert->grau = agcountuniqedges(g,v,1,1);
			vert->tipo = vert->nome[0];
			vert->vizinhos = iniciaLista();

			


			printf("Aloca vertice: %s com grau: %ld do tipo: %c\n", vert->nome, vert->grau, vert->tipo);
			insereLista(gr->vert, vert);			
			printf("------------------------------------------\n");					
	}
}

//------------------------------------------------------------------------------
// constrói a vizinhança dos vertices

void constroiViz(Agraph_t *g, grafo gr) {
	Agedge_t *a = NULL;
	for (a = agfstedge(g, v); a; a = agnxtedge(g, a, v)) {
		Agnode_t *tail = NULL;
		Agnode_t *head = NULL;

		tail = agtail(a);
		head = aghead(a);

		char *nome = agnameof(tail);
		if (nome[0] == 'c') {
			vertice aux = procuraLista(gr->vert,nome);
		}

		printf("%s -> %s\n", agnameof(tail), agnameof(head));
	}
}

//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot.
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 

grafo escreve_grafo(FILE *output, grafo g) {
  // agwrite(g,output);
  return NULL;
}
//------------------------------------------------------------------------------
// devolve o grafo de recomendações de g
//
// cada aresta {c,p} de H representa uma recomendação do produto p
// para o consumidor c, e tem um atributo "weight" que é um inteiro
// representando a intensidade da recomendação do produto p para o
// consumidor c.

grafo recomendacoes(grafo g){

  return g;
}

//------------------------------------------------------------------------------
