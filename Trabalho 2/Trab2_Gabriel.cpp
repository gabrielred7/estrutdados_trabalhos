#include <iostream>
#include <stdlib.h>
#include <cstring>

using namespace std;

typedef struct lista{
    int chave;
    int *adjunto;
    struct lista *proximo;
}tno;

tno* Insere(tno *ptlista, int index){
    tno *novo = (tno*) malloc(sizeof(tno));
    novo->chave = index;
    novo->proximo = ptlista;
    return novo;
}

tno* Busca(tno *lista, int x){
    if (lista == NULL){
        return NULL;
    }
    if (lista->chave==x){
        return lista;
    }
    return Busca(lista->proximo, x);
}

void Imprime(tno *lista){
    tno *atual;
    for (atual = lista; atual!=NULL; atual = atual->proximo){
        cout << atual->chave << endl;
    }
}

int main(){
    tno *ptLista, *listaBusca;

    //Inicializamos a primeira chave 0 como cabeça da lista
	ptLista = (tno *) malloc(sizeof(tno));
	ptLista->chave = 0;
	ptLista->proximo =NULL;

	char *linha = NULL;
  	size_t tamanho = 0;

	int vertices, arestas;
	scanf("%d %d\n",&vertices, &arestas);

	//Criamos um vetor grauEntrada para contar o Grau de Entrada de todos os Vertices
	int grauEntrada[vertices];
	for (int i = 0; i < vertices; i++){
		grauEntrada[i]=0;
	}

	//Criamos um vetor para ordem final dos vertices
	int ordenacao[vertices];

    // Aqui lemos o grafo do teclado
	for(int i = 1; i <= vertices; i++){
    	getline(&linha, &tamanho, stdin);
    	int posicao = 0;
    	int numLido = 0;
    	int numChars;

		ptLista = Insere(ptLista, i);
		ptLista->adjunto = (int *) malloc(0*sizeof(int));
		int linhaAtual = 0; 
    	
    	while (sscanf(&linha[posicao], " %d %n", &numLido, &numChars) > 0) {
      		posicao += numChars;
      		if(strlen(linha) != 0){
				ptLista->adjunto[linhaAtual]=numLido;
				linhaAtual++;//incrementa o contador para cada numero pego na linha
	  			//printf(" insere em adj [ %d ] o vertice %d\n",i, numLido);      
      			grauEntrada[numLido]++; //Incrementa o grau de entrada usando o numero lido
			}   
    	}
  	}

	//Procura os vertices com grau de entrada zero e coloca no vetor ordenacao
	int pos = 0;
	for(int v = 1; v <= vertices; v++){
		if(grauEntrada[v] == 0){
			ordenacao[pos] = v;
			pos++;
		}
	}
	//Desconta grau de entrada
	int k = 0; 
	int quantAdj; //auxiliar para guardar a conta
	while(k < pos){
		puts("Teste");
		//Buscamos aquele vertice que ja foi colocado na ordem
		//Com o vetor em mãos acessamos seus adjunto
		listaBusca = Busca(ptLista, ordenacao[k]);
		quantAdj = (sizeof(listaBusca->adjunto)/4);
		printf("Tamanho: %d \n", quantAdj);
		for(int j = 1; j <= quantAdj; j++){
			grauEntrada[j]--;
			if(grauEntrada[j] == 0){
				ordenacao[pos] = j;
				pos++;
			}				
		}
        k++;
	}

	for(int i = 0; i < vertices; i++){
		printf("Lista final: %d ", ordenacao[i]);
	}
}
