#ifndef _LISTA_H
#define _LISTA_H

#include <stdio.h>

//declara nó da lista
typedef struct noh *noh;

//declara lista
typedef struct lista *lista;

// inicia lista alocando memória e iniciando parâmetros
lista iniciaLista();

// libera lista da memória, um nó de cada vez, então a lista
void liberaLista(lista l);

// insere nó com conteúdo passado no final da lista
noh insereLista(lista l, void *cont);

// remove nó do final da lista
void removeLista(lista l);