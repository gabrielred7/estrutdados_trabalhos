/*
Trabalho 2 - Ordenação Topologica
Gabriel Almeida Mendes - DRE: 117204959
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ptno tno;
struct ptno{ 
	int num_vertice;
    int num_adjacente;
	int *adj;
	tno *proximo;
};
tno *ptlista;

// Função que cria o novo vértice
void insere_vertice(tno *ptlista,int num_vertice){ 
    tno *novo_vertice;
    novo_vertice = malloc(sizeof(tno));
    if (novo_vertice == NULL){ printf("Erro, overflow ao criar vertice!"); return;}
    novo_vertice->num_vertice = num_vertice;
    novo_vertice->proximo = ptlista->proximo;
    novo_vertice->adj = NULL;
    novo_vertice->num_adjacente = 0;
    ptlista->proximo = novo_vertice;
}

// Função que insere as arestas adjacentes ao vértice atual.
void insere_adjacente(tno *ptlista, int numero_lido, int index){
    tno *p;
    p = ptlista->proximo;
    p->adj = (int *) realloc(p->adj, (index+1) * sizeof(int));
    if (p->adj == NULL){ printf("Erro, overflow ao adicionar adj!"); return;}
    p->adj[index] = numero_lido;
    p->num_adjacente++;
}

// Função que retorna o ponteiro correto para o vertice atual.
tno* retorna_vertice(tno *ptlista, int index){
    if(ptlista == NULL){ return NULL;}
    if(ptlista->num_vertice == index){return ptlista;}
    return retorna_vertice(ptlista->proximo, index);
}

void imprime_vertice(tno *ptlista){
    tno *aux;
    for (aux = ptlista->proximo; aux != NULL; aux = aux->proximo){
        printf ("num vertice %d\n", aux->num_vertice);
    }
}

void imprime_adjacente(tno *ptlista){
    tno *aux;
    for (aux = ptlista->proximo; aux != NULL; aux = aux->proximo){
        for(int i = 0; i < aux->num_adjacente; i++)
            printf("num adj %d ", aux->adj[i]);
    }   
    printf("\n");
}

int main(){
    tno *ptlista;
    ptlista = (tno*) malloc(sizeof(tno));
    ptlista->proximo = NULL;

    char *linha = NULL;
    size_t tamanho = 0;
    
    int vertices, arestas, posicao;
    scanf("%d %d\n", &vertices, &arestas);
    
    int grau_entrada[vertices];
    int ordenacao[vertices];

    for(int i = 0; i < vertices; i++){
	    grau_entrada[i] = 0; 
	}

    for(int i = 1; i <= vertices; i++){ 
        getline(&linha, &tamanho, stdin);
        int posicao = 0, numero_lido = 0, index = 0;
        int numero_caracteres;
        insere_vertice(ptlista, i);

        while (sscanf(&linha[posicao], " %d %n", &numero_lido, &numero_caracteres) > 0){
            posicao += numero_caracteres;
            if(strlen(linha) != 0){
                insere_adjacente(ptlista, numero_lido, index); 
                index++;
                grau_entrada[numero_lido-1]++;
            }
        }
    }

    posicao = 0;
    for(int i = 0; i < vertices; i++){ 
        if(grau_entrada[i] == 0){
            ordenacao[posicao] = i+1;
            posicao++;
        }
    }
    int aux;
    tno *p;
    int i = 0; 
    while(i < posicao){
        p = retorna_vertice(ptlista, ordenacao[i]);
        for(int j = 0; j < p->num_adjacente; j++){
            aux = p->adj[j];
            grau_entrada[aux-1]--; 
            if (grau_entrada[aux-1] == 0){
                ordenacao[posicao] = aux;
                posicao++;
            }
        }
        i++;
    }
    // imprime_vertice a ordem topologica
    for(int i = 0; i < vertices; i++){ 
        printf("%d ", ordenacao[i]);
    }
    return 0;
}