#include "recomenda.h"
#include "grafo.h"

//------------------------------------------------------------------------------
// encontra o tamanho da intersecção entre a vizinhança dos dois vertices
// Γ(c1) ∩ Γ(c2)

int comparaViz(grafo g, vertice c1, vertice c2) {
	// printf("Intersec %s com %s\n", c1->nome, c2->nome);
	int intersec = 0;
	for(noh aux = g->vert->ini; aux; aux = aux->prox) {
		vertice v = (vertice) aux->cont;
		if (v->tipo[0] == 'p') {
			// printf("Analisando %s\n", v->nome);
			if (procuraAres(v->vizinhos->ini,c1) && procuraAres(v->vizinhos->ini,c2))
				intersec++;
		}
	}
	return intersec;
}

//------------------------------------------------------------------------------
// encontra a diferença entre a vizinhança dos dois vertices
// Γ(c1) - Γ(c2)

lista encontraDif(vertice c1, vertice c2) {
	// printf("Dif %s com %s\n", c1->nome, c2->nome);
	lista dif = iniciaLista();
	for(noh aux = c1->vizinhos->ini; aux; aux = aux->prox) {
		aresta a = (aresta) aux->cont;
		if (!procuraAres(c2->vizinhos->ini,a->vert)) {
			insereLista(dif,a->vert);
		}
	}
	return dif;
}

//------------------------------------------------------------------------------
// copia os vertices de um grafo existente para um novo grafo

grafo copiaGrafo(grafo orig) {
  grafo dest = criaGrafo((char*)"recomendacoes",0,orig->v,0);

  if (TEST) printf("------------------------------------------\n");
  for (noh aux = orig->vert->ini; aux; aux = aux->prox) {
      vertice origVert = (vertice) aux->cont;
      vertice vert = criaVert(origVert->nome,origVert->grau,origVert->tipo);
      
			if (TEST) printf("Aloca vertice: %s com grau: %ld do tipo: %s\n", vert->nome, vert->grau, vert->tipo);
			insereLista(dest->vert, vert);			
			if (TEST) printf("------------------------------------------\n");					
  }

  return dest;
}

//------------------------------------------------------------------------------
// devolve o grafo de recomendações de g
//
// cada aresta {c,p} de H representa uma recomendação do produto p
// para o consumidor c, e tem um atributo "peso" que é um inteiro
// representando a intensidade da recomendação do produto p para o
// consumidor c.

grafo recomendacoes(grafo gr) {
	grafo rec = copiaGrafo(gr);
  for (noh aux = gr->vert->ini; aux; aux = aux->prox) {
    vertice c1 = (vertice)aux->cont;
    if (c1->tipo[0] == 'p')
      continue;
    for (noh aux2 = gr->vert->ini; aux2; aux2 = aux2->prox) {
      vertice c2 = (vertice)aux2->cont;
      if (c2->tipo[0] == 'p' || c1 == c2)
        continue;
      
      int i = comparaViz(gr,c1,c2);
      if (TEST) printf("------------------------------------------\n");
      if (TEST) printf("Intersec de %s com %s: %d\n", c1->nome,c2->nome,i);

      lista l = encontraDif(c1,c2);
      if (TEST) printf("Dif de %s com %s: %ld\n", c1->nome,c2->nome,l->tam);

      if (i >= l->tam) {
        if (TEST) imprimeVert(l->ini,0);
        vertice v = procuraVert(rec->vert,c2->nome);
        adicionaAres(l->ini,v,rec);
        rec->a += l->tam;
        // for (noh aux3 = l->ini; aux3; aux3 = aux3->prox) {
        //   vertice paux = (vertice)aux3->cont;
        //   vertice p = procuraVert(rec->vert,paux->nome);
        //   insereAres(p,v);
        //   rec->a++;
        // }
      }
    }
  }

  return rec;
}

//------------------------------------------------------------------------------
// adiciona aresta de recomendação ou aumenta o peso se já existir

noh adicionaAres(noh aux, vertice v, grafo rec) {
  if (!aux)
    return aux;
  vertice paux = (vertice) aux->cont;
  vertice p = procuraVert(rec->vert,paux->nome);
  insereAres(v,p);
  insereAres(p,v);
  return adicionaAres(aux->prox,v,rec);
}

void insereAres(vertice v1, vertice v2) {
  aresta ares = procuraAres(v1->vizinhos->ini,v2);
  if (!ares) {
    ares = criaAres(v2,1);
    if (TEST) printf("Adiciona aresta %s -> %s\n", v1->nome, ares->vert->nome);
    insereLista(v1->vizinhos, ares);
  } else {
    ares->peso++;
  }
}