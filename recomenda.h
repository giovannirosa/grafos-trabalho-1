#ifndef RECOMENDA_H
#define RECOMENDA_H

#include "grafo.h"

int comparaViz(grafo g, vertice c1, vertice c2);
lista encontraDif(vertice c1, vertice c2);
grafo recomendacoes(grafo gr);
grafo copiaGrafo(grafo orig);
noh adicionaAres(noh aux, vertice v);

#endif