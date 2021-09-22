// Gabriel Almeida Mendes - DRE: 117204959
// Trabalho 1 - grafo e ordenação topologica
/* Leia um grafo da entrada (teclado), e imprima uma ordenacao topologica valida. 
Voce deve utilizar o algoritmo descrito em aula, ou seja, calcular o grau de entrada 
dos vertices, e utilizar o grau de entrada para obter a ordenacao. Nao utilize busca 
em profundidade. O grafo deve ser implementado utilizando listas encadeadas 
(um vetor de listas encadeadas). */

#include<stdio.h>
#include<stdlib.h>
#include<string>

typedef struct _tno{
    int nVertices;
    int *adj;
    struct _tno *proximo;
} tno;

int main(){
    char *linha = NULL;
    size_t tamLinha = 0;
    int vert, arest, i;

}