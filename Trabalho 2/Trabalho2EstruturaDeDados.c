#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ptno{ //cria o tipo tno que guarda o número do vértice, seus adjacentes e o endereço do próx vertice
	int numVertice;
    int num_adjacente;
	int *adj;
	struct ptno *prox;
} tno;

void insere_vertice(tno * ptlista,int numVertice){ 
    // função que irá criar o novo vértice, alocando o mesmo na memória e guardando a posição dele em uma lista encadeada com ptCabeça

    tno *novo;
    novo = malloc(sizeof(tno));
    if (novo == NULL){
        printf("Erro, overflow ao criar vertice!");
        return;
    }
    novo->numVertice = numVertice;
    novo->prox = ptlista->prox;
    novo->adj = NULL;
    novo->num_adjacente = 0;
    ptlista->prox = novo;
}

void insere_adjacente(tno * ptlista, int numLido, int index){
    // função que irá inserir, 1 por 1, as arestas adjacentes ao vértice atual, alocando cada um na memória.
    
    tno *p;
    p = ptlista->prox;
    p->adj = (int *) realloc(p->adj, (index+1) * sizeof(int));
    if (p->adj == NULL){
        printf("Erro, overflow ao adicionar adj!");
        return;
    }
    p->adj[index] = numLido;
    p->num_adjacente++;
}

tno * retorna_vertice(tno * ptlista, int index){
    // função para retornar o ponteiro correto para o vertice atual. Não funciona se pegar o vertice direto na main.
    if(ptlista == NULL){
        return NULL;
    }
    if(ptlista->numVertice == index){
        return ptlista;
    }
    return retorna_vertice(ptlista->prox, index);
}

void imprime(tno *ptlista){
    tno *p;
    for (p = ptlista->prox; p != NULL; p = p->prox){
        printf ("num vertice %d\n", p->numVertice);
    }
}

void imprime_adjacente(tno *ptlista){
    tno *p;
    for (p = ptlista->prox; p != NULL; p = p->prox){
        for(int i = 0; i < p->num_adjacente; i++)
            printf("num adj %d ", p->adj[i]);
    }   printf("\n");
}

int main(){
    tno *ptlista;
    ptlista =(tno *) malloc(sizeof (tno));
    ptlista->prox=NULL;
    char *linha = NULL;
    size_t tamLinha = 0;
    int vertices, arestas, i, j, pos;
    scanf("%d %d\n", &vertices, &arestas);
    //printf("Li vertices = %d e arestas = %d\n",vertices,arestas);
    int grauEnt[vertices]; // cria um vetor para guardar o grau de entrada dos vertices
    int ordem[vertices]; // cria um vetor do tamanho dos vertices para gravar a ordem topologica final

    for (i = 0; i < vertices; i++){
	    grauEnt[i] = 0; //zera o grau dos vertices para iniciar sempre em 0 quando pegar o grau exato
	}

    for(i = 1; i <= vertices; i++){ // lendo cada linha e seus adj's
    
        getline(&linha, &tamLinha, stdin);
        int pos = 0;
        int numLido = 0;
        int numChars;
        int index = 0;
        insere_vertice(ptlista, i);

        while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0){ // lendo cada adj do vertice atual
            pos += numChars;
            if(strlen(linha) != 0){
	            //printf("insere em adj [ %d ] o vertice %d, while: %d\n", i, numLido, index);
                insere_adjacente(ptlista, numLido, index); // chama a função para inserir no vértice os seus adjacentes
                index++; // aumenta o index para em cada vertice ter salvo o numero de adj's que ele tem
                grauEnt[numLido-1]++; // aumenta o grau de entrada do vertice lido pois ele é adj de outro vertice
            }
        }
    }

    pos = 0;
    for(i = 0; i < vertices; i++){ // verifica o grau dos vertices para colocar na lista de ordem
        if(grauEnt[i] == 0){
            ordem[pos] = i+1;
            pos++;
        }
    }
    int aux;
    i = 0; // zera o contador auxiliar i
    tno *p;
     // pega o primeiro item da lista
    while(i < pos){ // enquanto o aux i for menor que o aux pos
        p = retorna_vertice(ptlista, ordem[i]);
        //printf("loop: %d - vertice atual: %d\n", i,  p->numVertice);
        for(j = 0; j < p->num_adjacente; j++){
            aux = p->adj[j];
            grauEnt[aux-1]--; // diminui o grau de entrada do vertice que é adj de outro vertice
            //printf("j: %d - adj do vertice atual: %d\n", j, aux);
            if (grauEnt[aux-1] == 0){
                ordem[pos] = aux;
                pos++;
            }
        }
        i++; // continua o loop while
    }

    for(i = 0; i < vertices; i++){ // imprime a ordem topologica
        printf("%d ", ordem[i]);
    }
    return 0;
}