#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
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
	printf("------------------------------------------\n");
  printf("Nome: %s | Dir: %d | Vert: %d | Arest: %d\n", g->nome, g->dir, g->v, g->a);
	imprimeVert(g->vert->ini,1);
	printf("------------------------------------------\n");
}

noh imprimeVert(noh aux, int ares) {
	if (!aux)
		return aux;
	vertice v = (vertice) aux->cont;
	printf("%s->", v->nome);
	if (ares)
		imprimeAres(v->vizinhos->ini);
	printf("\n");
	return imprimeVert(aux->prox,ares);
}

noh imprimeAres(noh aux) {
	if (!aux)
		return aux;
	aresta a = (aresta) aux->cont;
	printf("%s(%ld)->", a->vert->nome, a->peso);
	return imprimeAres(aux->prox);
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
	// printf("Aloca grafo\n");

	g = agread(input, NULL);
	gr->nome = agnameof(g);
	gr->dir = agisdirected(g);	 
	gr->v = agnnodes(g);
	gr->a = agnedges(g);

	insereVert(g,gr);
	constroiViz(g,gr);
  imprimeGrafo(gr);

	agclose(g);
  printf("Grafo lido.\n");

	noh aux = gr->vert->ini;
	int i = comparaViz(gr,(vertice)aux->cont,(vertice)aux->prox->cont);
	printf("Intersec: %d\n", i);

	lista l = encontraDif((vertice)aux->cont,(vertice)aux->prox->cont);
	printf("Dif: %ld\n", l->tam);
	imprimeVert(l->ini,0);

	return gr;
}

//------------------------------------------------------------------------------
// insere os vertices ao grafo

void insereVert(Agraph_t *g, grafo gr) {
	Agnode_t *v = NULL;
	gr->vert = iniciaLista();

	printf("------------------------------------------\n");
  for(v = agfstnode(g); v; v = agnxtnode(g,v)) {	        	
      vertice vert = malloc(sizeof(struct vertice));
			vert->nome = agnameof(v);
			vert->grau = agcountuniqedges(g,v,1,1);
			vert->tipo = agget(v,(char*)"tipo")[0];
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
	Agnode_t *v = NULL;

	for(v = agfstnode(g); v; v = agnxtnode(g,v)) {
		printf("------------------------------------------\n");
		printf("Construindo vizinhança do %s\n", agnameof(v));
		for (a = agfstedge(g, v); a; a = agnxtedge(g, a, v)) {
			Agnode_t *tail = NULL;
			Agnode_t *head = NULL;

			tail = agtail(a);
			head = aghead(a);
			// printf("Tail: %s Head: %s\n", agnameof(tail), agnameof(head));

			vertice auxTail = NULL;
			vertice auxHead = NULL;
			char tipo = agget(v,(char*)"tipo")[0];
			if (tipo == 'c') {
				auxTail = procuraLista(gr->vert,agnameof(tail));
				auxHead = procuraLista(gr->vert,agnameof(head));
			} else if (tipo == 'p') {
				auxTail = procuraLista(gr->vert,agnameof(head));
				auxHead = procuraLista(gr->vert,agnameof(tail));
			}

			// printf("Achou tail: %s Achou head: %s\n", auxTail->nome, auxHead->nome);

			aresta ares = malloc(sizeof(struct aresta));
			ares->vert = auxHead;
			ares->peso = 1;

			insereLista(auxTail->vizinhos, ares);
			printf("Inseriu aresta: %s -> %s\n", auxTail->nome, ares->vert->nome);
		}
	}
}

// procura lista pelo conteudo e retorna o vertice ou NULL se nao encontrar
vertice procuraLista(lista l, char *p) {
	// printf("Procura lista...\n");
  noh aux = l->ini;
	// if (!aux)
	// 	printf("lista vazia\n");
  while(aux) {
		vertice v = (vertice) aux->cont;
		// printf("Compara: %s com %s\n", v->nome, p);
    if (strcmp(v->nome,p) == 0)
      return v;
    
    aux = aux->prox;
  }
  return NULL;
}

// Γ(c1) ∩ Γ(c2)
int comparaViz(grafo g, vertice c1, vertice c2) {
	printf("Intersec %s com %s\n", c1->nome, c2->nome);
	noh aux = NULL;
	int intersec = 0;
	for(aux = g->vert->ini; aux; aux = aux->prox) {
		vertice v = (vertice) aux->cont;
		if (v->tipo == 'p') {
			// printf("Analisando %s\n", v->nome);
			if (contemVert(v->vizinhos->ini,c1) && contemVert(v->vizinhos->ini,c2))
				intersec++;
		}
	}
	return intersec;
}

int contemVert(noh aux, vertice v) {
	if (!aux)
		return 0;
	aresta a = (aresta) aux->cont;
	// printf("Comparando %s com %s\n", v->nome, a->vert->nome);
	if (strcmp(v->nome,a->vert->nome) == 0)
		return 1;
	return contemVert(aux->prox,v);
}

// Γ(c1) - Γ(c2)
lista encontraDif(vertice c1, vertice c2) {
	printf("Dif %s com %s\n", c1->nome, c2->nome);
	lista dif = iniciaLista();
	for(noh aux = c1->vizinhos->ini; aux; aux = aux->prox) {
		aresta a = (aresta) aux->cont;
		if (!contemVert(c2->vizinhos->ini,a->vert)) {
			insereLista(dif,a->vert);
		}
	}
	return dif;
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
