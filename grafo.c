#include <stdio.h>
#include <C:/Program Files (x86)/Graphviz2.38/include/graphviz/gvc.h>
#include <C:/Program Files (x86)/Graphviz2.38/include/graphviz/cgraph.h>
#include "grafo.h"

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// 
// o grafo pode ser direcionado ou não
// 
// o grafo tem um nome, que é uma "string"

struct grafo {
  char* nome;
  char dir;
  lista* l;
};

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
  printf("vai ler");
  Agraph_t* G = agread(input, 0);
  printf("leu");
  
  return NULL;
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
