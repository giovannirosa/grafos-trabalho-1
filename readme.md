# Grafos Trabalho 1

Trabalho 1 da matéria de Grafos do primeiro semestre de 2018, Universidade Federal do Paraná - UFPR.

## Começando

Existe um makefile neste diretório com os seguintes comandos disponíveis:

* make: compila os arquivos teste.c, recomenda.c, grafo.c, lista.c e produz o executável teste
* make clean: limpa os arquivos .o
* make rebuild: make clean + make

### Pré-requisitos

É necessario ter o gcc e a biblioteca cgraph-dev instalada.

## Testando

É possível testar o programa com um passo a passo tendo stdout como saída.

### Como ativar os testes

Existem duas variáveis que podem ativar duas funcionalidades de teste que estão no arquivo grafo.h.

* TEST: assinando o valor 1, será impresso o passo a passo do código para facilitar o rastreamento.
* SIMPLIFICADO: assinando o valor 1, será impresso um grafo de saída simplificado para facilitar na verificação.

Utilize o comando make rebuild após mudar o valor dessas variáveis para compilar com mais agilidade.

Exemplo com entrada 2.dot:
```
SIMPLIFICADO = 0
graph recomendacoes {
  c1 [tipo=c]
  c2 [tipo=c]
  c3 [tipo=c]
  pa [tipo=p]
  pb [tipo=p]
  pc [tipo=p]
  c2 -- pa [peso=1]
  c3 -- pc [peso=1]
  pa -- c2 [peso=1]
  pc -- c3 [peso=1]
}
```
```
SIMPLIFICADO = 1
graph recomendacoes {
  c1
  c2->pa[1]
  c3->pc[1]
  pa->c2[1]
  pb
  pc->c3[1]
}
```

## Built With

* [gcc](https://gcc.gnu.org/) - The GNU Compiler Collection
* [Graphviz](https://graphviz.org/) - Graphviz is open source graph visualization software

## Authors

* **Giovanni Rosa** - [giovannirosa](https://github.com/giovannirosa)

## Licença

Código aberto, qualquer um pode usar para qualquer propósito.

## Acknowledgments

* C não é produtivo