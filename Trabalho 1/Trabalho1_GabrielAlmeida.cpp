// Gabriel Almeida Mendes - DRE: 117204959
// Trabalho 1 - merge Sort
// Leia numeros da entrada, armazene-os na memoria, e ordene utilizando o merge Sort. Imprima os numeros ordenados.

#include <iostream>
#include <stdlib.h>

using namespace std;

void merge(int *vetor, int inicio, int meio, int final){ 
	//Inicialização de variaveis
	int *varTemporaria, posicao1, posicao2, tamanhoVetor; 
	bool bl1 = false, bl2 = false; 
	int j, k;
	tamanhoVetor = final - inicio + 1;
	posicao1 = inicio; 
	posicao2 = meio + 1; 

	//Alocação de memoria
	varTemporaria = (int*) malloc(sizeof(int) * tamanhoVetor);

	//Verificando a alocação do vetor
	if (varTemporaria != NULL){ 
		for (int i = 0; i< tamanhoVetor; i++){
			if(!bl1 && !bl2){ 
				if(vetor[posicao1] < vetor[posicao2])
					varTemporaria[i]= vetor[posicao1++];
				else
				varTemporaria[i]= vetor[posicao2++]; 
				
				if(posicao1 > meio){ bl1 = true; }	
				if(posicao2 > final){ bl2 = true; }

			} else { 
				if(!bl1){
					varTemporaria[i] = vetor[posicao1++];
				} else {
					varTemporaria[i] = vetor[posicao2++];
				}
			}
		}
		// Ordenando os valores no vetor-ponteiro original
		for(j = 0, k = inicio; j < tamanhoVetor; j++, k++){
			vetor[k] = varTemporaria[j];
		}
	}
	free(varTemporaria); 
}

//Função Recursiva para o Mergesort
void mergesort(int *vetor, int inicio, int fim){ 
	//Cuida para que cada vetor tenha apenas 1 elemento
	int meio; 
	if(inicio < fim){ 
		meio = (inicio + fim)/2; 
		mergesort(vetor, inicio, meio); 
		mergesort(vetor, meio + 1, fim); 
		//Chama a função auxiiar de ordenação
		merge(vetor, inicio, meio, fim);
	}
}

int main(int argc, char *argv[]) {
	int num; //variavel do teclado (usuario)
	int *vetor;

	//Alocação de memoria
	vetor = (int *) malloc(0 *sizeof(int)); 

	//Descobrindo a quantidade de linhas
	int linhaAtual = 0; 
	while (!feof(stdin)){ //codigo visto em aula
		if (scanf("%d", &num) == 1){
			//Realocação de memoria dado o tamanho do vetor para caber + um numero descoberto 	
			vetor = (int*) realloc(vetor, sizeof(int) * (linhaAtual + 1));
			vetor[linhaAtual] = num; 
			linhaAtual++;
		}
	}
	
	//Chama a função de ordenação
	mergesort(vetor, 0, linhaAtual - 1);
	
	//Resposta final
	for(num = 0; num < linhaAtual; num++){ 
		cout << vetor[num] << endl;
	}
}