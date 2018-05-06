#include "grafo.h"

//------------------------------------------------------------------------------
// MÉTODOS DE IMPRESSÃO - TESTE
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// imprime o grafo com seus parâmetros e informações relevantes
// usado para testes

void imprimeGrafo(grafo g) {
	printf("------------------------------------------\n");
  printf("Nome: %s | Dir: %ld | Vert: %ld | Arest: %ld\n", g->nome, g->dir, g->v, g->a);
	imprimeVert(g->vert->ini,1);
	printf("------------------------------------------\n");
}

//------------------------------------------------------------------------------
// imprime os vertices com seus parâmetros e informações relevantes
// usado para testes

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

//------------------------------------------------------------------------------
// imprime as arestas com seus parâmetros e informações relevantes
// usado para testes

noh imprimeAres(noh aux) {
	if (!aux)
		return aux;
	aresta a = (aresta) aux->cont;
	if (TEST) printf("%s(%ld)->", a->vert->nome, a->peso);
	return imprimeAres(aux->prox);
}

//------------------------------------------------------------------------------
// MÉTODOS DE CRIAÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// cria um novo grafo alocando memória e definindo suas variáveis

grafo criaGrafo(char *nome, long dir, long vert, long ares) {
  grafo gr = malloc(sizeof(struct grafo));
  gr->nome = nome;
	gr->dir = dir;	 
	gr->v = vert;
	gr->a = ares;
  gr->vert = iniciaLista();
  return gr;
}

//------------------------------------------------------------------------------
// cria um novo vertice alocando memória e definindo suas variáveis

vertice criaVert(char *nome, long grau, char *tipo) {
  vertice vert = malloc(sizeof(struct vertice));
  vert->nome = nome;
  vert->grau = grau;
  vert->tipo = tipo;
  vert->vizinhos = iniciaLista();
  return vert;
}

//------------------------------------------------------------------------------
// cria uma nova aresta alocando memória e definindo suas variáveis

aresta criaAres(vertice v, long peso) {
  aresta ares = malloc(sizeof(struct aresta));
  ares->vert = v;
  ares->peso = peso;
  return ares;
}

//------------------------------------------------------------------------------
// MÉTODOS DE INSERÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// insere os vertices ao grafo

void insereVert(Agraph_t *g, grafo gr) {
	if (TEST) printf("------------------------------------------\n");
  for(Agnode_t *v = agfstnode(g); v; v = agnxtnode(g,v)) {  	
      vertice vert = criaVert(agnameof(v),agcountuniqedges(g,v,1,1),agget(v,(char*)"tipo"));
			if (TEST) printf("Aloca vertice: %s com grau: %ld do tipo: %s\n", vert->nome, vert->grau, vert->tipo);
			insereLista(gr->vert, vert);			
			if (TEST) printf("------------------------------------------\n");					
	}
}

//------------------------------------------------------------------------------
// constrói a vizinhança dos vertices

void constroiViz(Agraph_t *g, grafo gr) {
	for(Agnode_t *v = agfstnode(g); v; v = agnxtnode(g,v)) {
		if (TEST) printf("------------------------------------------\n");
		if (TEST) printf("Construindo vizinhança do %s\n", agnameof(v));
		for (Agedge_t *a = agfstedge(g, v); a; a = agnxtedge(g, a, v)) {
			Agnode_t *tail = NULL;
			Agnode_t *head = NULL;

			tail = agtail(a);
			head = aghead(a);
			// printf("Tail: %s Head: %s\n", agnameof(tail), agnameof(head));

			vertice auxTail = NULL;
			vertice auxHead = NULL;
      
			char tipo = agget(v,(char*)"tipo")[0];
			if (tipo == 'c') {
				auxTail = procuraVert(gr->vert,agnameof(tail));
				auxHead = procuraVert(gr->vert,agnameof(head));
			} else if (tipo == 'p') {
				auxTail = procuraVert(gr->vert,agnameof(head));
				auxHead = procuraVert(gr->vert,agnameof(tail));
			}

			// printf("Achou tail: %s Achou head: %s\n", auxTail->nome, auxHead->nome);

			aresta ares = criaAres(auxHead,1);
			insereLista(auxTail->vizinhos, ares);
			if (TEST) printf("Inseriu aresta: %s -> %s\n", auxTail->nome, ares->vert->nome);
		}
	}
}

//------------------------------------------------------------------------------
// MÉTODOS DE BUSCA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna o vertice ou NULL se nao encontrar

vertice procuraVert(lista l, char *p) {
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

//------------------------------------------------------------------------------
// procura lista pelo conteudo e retorna a aresta ou NULL se nao encontrar

aresta procuraAres(noh aux, vertice v) {
	if (!aux)
		return NULL;
	aresta a = (aresta) aux->cont;
	// printf("Comparando %s com %s\n", v->nome, a->vert->nome);
	if (strcmp(v->nome,a->vert->nome) == 0)
		return a;
	return procuraAres(aux->prox,v);
}

//------------------------------------------------------------------------------
// MÉTODOS DE LEITURA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// lê um grafo no formato dot de input
// 
// devolve o grafo lido,
//         ou 
//         NULL, em caso de erro 

grafo leGrafo(FILE *input) {
  if (TEST) printf("Lendo grafo do arquivo...\n");
	Agraph_t *g = agread(input, NULL);
  grafo gr = criaGrafo(agnameof(g),agisdirected(g),agnnodes(g),agnedges(g));

	insereVert(g,gr);
	constroiViz(g,gr);
  if (TEST) imprimeGrafo(gr);

	agclose(g);
  if (TEST) printf("Grafo lido.\n");

	return gr;
}

//------------------------------------------------------------------------------
// MÉTODOS DE ESCRITA
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// escreve o grafo g em output usando o formato dot.
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 

grafo escreveGrafo(FILE *output, grafo g) {
  Agraph_t *gr = transformaGrafo(g);
  agwrite(gr,output);
  if (TEST) imprimeGrafo(g);
  return g;
}

Agraph_t* transformaGrafo(grafo g) {
	Agraph_t *gr = agopen((char*)"recomendacoes", Agundirected, NULL);

	imprimeGrafo(g);
	transformaVert(g->vert->ini,gr);

	// for (noh aux = g->vert->ini; aux; aux = aux->prox) {
	// 	vertice v = (vertice) aux->cont;
	// 	for (noh aux2 = v->vizinhos->ini; aux2; aux2 = aux2->prox) {
	// 		aresta a = (aresta) aux2->cont;

	// 		Agnode_t *x = agnode(gr,v->nome,FALSE);
	// 		Agnode_t *y = agnode(gr,a->vert->nome,FALSE);

	// 		printf("criando aresta %s -> %s\n", v->nome,a->vert->nome);
	// 		agedge(gr,x,y,NULL,TRUE);
	// 	}
	// }

	return gr;
}

noh transformaVert(noh aux, Agraph_t *gr) {
	if (!aux)
		return aux;
	vertice v = (vertice) aux->cont;
	printf("criando vert %s\n", v->nome);
	agnode(gr,v->nome,TRUE);
	return transformaVert(aux->prox,gr);
}

//------------------------------------------------------------------------------
// MÉTODOS DE DESTRUIÇÃO
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroiGrafo(grafo g) {

  return 0;
}

//------------------------------------------------------------------------------
