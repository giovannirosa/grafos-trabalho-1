#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "lista.h"

// nó da lista com conteudo, proximo e anterior
struct noh {
	void *cont;
	noh prox, ant;
};

// lista com inicio, fim e tamanho
struct lista {
	noh ini, fim;
	long tam;
};

// inicia lista alocando memória e iniciando parâmetros
lista iniciaLista(void) {
  lista l = malloc(sizeof(struct lista));

  l->tam = 0;
  l->ini = NULL;
  l->fim = NULL;

  return l;
}

// libera lista da memória, um nó de cada vez, então a lista
void liberaLista(lista l) { 
  noh aux;
  while((aux = l->fim)) {
    l->fim = l->fim->ant;
    free(aux);
  }
  free(l);
}

// insere nó com conteúdo passado no final da lista
noh insereLista(lista l, void *cont) {
  noh aux = malloc(sizeof(struct noh));
  printf("Aloca noh\n");

  l->tam++;
  aux->cont = cont;
  aux->ant = l->fim;
  aux->prox = NULL;
  
  return l->fim = aux;
}

// remove nó do final da lista
void removeLista(lista l) {
  noh aux = l->fim;

  l->tam--;
  l->fim = (l->fim)->ant;
  l->fim->prox = NULL;
  free(aux);
}

// procura lista pelo conteudo e retorna o noh ou NULL se nao encontrar
noh procuraLista(lista l, void* p) {
  noh aux = l->ini;
  while(aux) {
    if (aux->cont == p)
      return aux;
    
    aux = aux->prox;
  }
  return NULL;
}