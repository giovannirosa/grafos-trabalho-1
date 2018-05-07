#ifndef RECOMENDA_H
#define RECOMENDA_H

#include "grafo.h"

//------------------------------------------------------------------------------
// encontra o tamanho da intersecção entre a vizinhança dos dois vertices
// Γ(c1) ∩ Γ(c2)

int comparaViz(grafo g, vertice c1, vertice c2);

//------------------------------------------------------------------------------
// encontra a diferença entre a vizinhança dos dois vertices
// Γ(c1) - Γ(c2)

lista encontraDif(vertice c1, vertice c2);

//------------------------------------------------------------------------------
// devolve o grafo de recomendações de g
//
// cada aresta {c,p} de H representa uma recomendação do produto p
// para o consumidor c, e tem um atributo "peso" que é um inteiro
// representando a intensidade da recomendação do produto p para o
// consumidor c.

grafo recomendacoes(grafo gr);

//------------------------------------------------------------------------------
// copia os vertices de um grafo existente para um novo grafo

grafo copiaGrafo(grafo orig);

//------------------------------------------------------------------------------
// adiciona aresta de recomendação ou aumenta o peso se já existir

noh adicionaAres(noh aux, vertice v, grafo rec);
void insereAres(vertice v1, vertice v2);

#endif