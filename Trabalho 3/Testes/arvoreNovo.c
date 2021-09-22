#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tno ArvAVL;

struct tno{
    int chave;
    ArvAVL *esq;
    ArvAVL *dir;
    int alt;  
};

ArvAVL *ptraiz; //ponteiro para ponteiro do tipo arvore avl

int maior(int a, int b);

//pega a altura da arvore
int altura_no(ArvAVL *no){
    if (no == NULL){return 0;}
    return no->alt;
}

//funcao que pega o maior valor
int maior(int a, int b){
    return (a > b) ? a : b;
}

/* Função auxiliar que aloca um novo nó/arvore com a chave fornecida*/
ArvAVL* novoNo(int valor){
    ArvAVL* novo;
    novo = (ArvAVL*) malloc(sizeof(ArvAVL));
    if (novo == NULL){printf("ERRO NÃO CONSEGUI ALOCAR  novo tno"); return novo;}

    //inicializar o primeiro no    
    novo->chave = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->alt = 1;
    //novo no e inicializado adicionad na folha
    return novo;
}


// Uma função de utilidade para girar à direita a subárvore enraizada com ptraiz
ArvAVL *rotacaoDireita(ArvAVL *ptraiz){
    ArvAVL *no = ptraiz->esq;
    ArvAVL *T = no->dir; //auxiliar
     
    //Faz a rotaçao
    no->dir = ptraiz;
    ptraiz->esq = T;

    //calcula as novas alturas
    ptraiz->alt = maior(altura_no(ptraiz->esq), altura_no(ptraiz->dir)) +1;
    no->alt = maior(altura_no(no->esq), altura_no(no->dir)) +1;
    
    //retorna a nova raiz
    return no;
}

ArvAVL *rotacaoEsquerda(ArvAVL *ptraiz){
    ArvAVL *no = ptraiz->dir;
    ArvAVL *T = no->esq; //auxiliar

    //Faz a rotacao
    no->esq = ptraiz;
    ptraiz->dir = T;

    //calcula as novas altura
    ptraiz->alt = maior(altura_no(ptraiz->esq), altura_no(ptraiz->dir)) +1; 
    no->alt = maior(altura_no(no->esq), altura_no(no->dir)) +1;
    
    //Retorna nova raiz
    return no;
}

//funcao auxiliar que calcula o fator de balanceamento
int fator_balanceamento(ArvAVL *no){
    if (no == NULL){return 0;}
    return (altura_no(no->esq) - altura_no(no->dir));
}

// Função recursiva para inserir uma chave na subárvore enraizada com nó e retorna a nova raiz da subárvore. 
ArvAVL* insere(ArvAVL* ptraiz, int valor){
    if (ptraiz == NULL){
        return novoNo(valor);
    }
    if (valor < ptraiz->chave){
        ptraiz->esq = insere(ptraiz->esq, valor);
    } else if (valor > ptraiz->chave){
        ptraiz->dir = insere(ptraiz->dir, valor);
    } else {
        return ptraiz;
    }
    
    /* Atualizar a altura do nó ancestral */ 
    ptraiz->alt = 1 + maior(altura_no(ptraiz->esq), altura_no(ptraiz->dir));

    int balanco = fator_balanceamento(ptraiz);

    if(balanco > 1){
        if(valor < ptraiz->esq->chave){
            //Left Left Case
            return rotacaoDireita(ptraiz);
        } else if(valor > ptraiz->esq->chave) {
            ptraiz->esq = rotacaoEsquerda(ptraiz->esq);
            return rotacaoDireita(ptraiz);  
        } 
    }

    if(balanco < -1){
        if(valor > ptraiz->dir->chave){
            //Right Right Case
            return rotacaoEsquerda(ptraiz);
        } else if(valor < ptraiz->dir->chave){
            //Right Left Case
            ptraiz->dir = rotacaoDireita(ptraiz->dir);
            return rotacaoEsquerda(ptraiz);
        }
        
    }
    
    /* retorna o ponteiro do nó (inalterado) */ 
    return ptraiz;
}

void imprime(ArvAVL *ptraiz){
    if (ptraiz != NULL){
        printf("%i(%i) ", ptraiz->chave, altura_no(ptraiz));
        imprime(ptraiz->esq);
        imprime(ptraiz->dir);
    }
}

int main(int argc, char *argv[]){
    char str[1]; //variavel string do teclado
    int num = 0; //variavel numerica do teclado (ususario)
    printf("comecei\n");
    bool laco = true;
    while(laco){
        if(scanf("%s", str) == 1){
            if(str[0] == 'p'){
                imprime(ptraiz);
                laco = true;
            }
            if(str[0] == 'i'){              
                if(scanf("%d", &num) == 1){       
                    ptraiz = insere(ptraiz, num);
                }
                laco = true;
            }
            if (str[0] == 's'){
                laco = false;
            }
        }
    }
    return 0;
}