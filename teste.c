#include "recomenda.h"
//------------------------------------------------------------------------------

int main(void) {
  grafo g = leGrafo(stdin);

  if ( !g )
    return 1;

  grafo rec = recomendacoes(g);
  escreveGrafo(stdout, rec);

  return ! destroiGrafo(g);
}