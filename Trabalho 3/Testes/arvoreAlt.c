#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tno ArvAVL;

struct tno{
    int chave;
    int alt;
    ArvAVL *esq;
    ArvAVL *dir;  
};

ArvAVL *ptraiz; //ponteiro para ponteiro do tipo arvore avl

int altura_no(ArvAVL *no){
    if (no == NULL){
        return -1;
    } else {
        return no -> alt;
    }
}

int maior(int a, int b){
    return (a > b) ? a : b;
}

int fator_balanceamento(ArvAVL *no){
    return (altura_no(no->esq) - altura_no(no->dir));
}

void imprime(ArvAVL *ptraiz){
    if (ptraiz != NULL){
        printf("%i(%i) ", ptraiz->chave, altura_no(ptraiz));
        imprime(ptraiz->esq);
        imprime(ptraiz->dir);
    }
}

ArvAVL* RotacaoLL(ArvAVL *ptraiz){ //ptraiz e o nó que se quer balancear
    printf("Chegou Aqui LL\n");
    ArvAVL* no = ptraiz->esq;
    ArvAVL* T = no->dir; //auxiliar
     
    //Faz a rotaçao
    no->dir = ptraiz;
    ptraiz->esq = T;
    printf("Fez a rotacao\n");

    //calcula as novas alturas
    ptraiz->alt = maior(altura_no(ptraiz->esq), altura_no(ptraiz->dir)) +1;
    no->alt = maior(altura_no(no->esq), altura_no(no->dir)) + 1;
    printf("Calculou a altura\n");
    
    //retorna a nova raiz
    ptraiz = no;
    return no;
}

ArvAVL* RotacaoRR(ArvAVL *ptraiz){
    
    ArvAVL* no = ptraiz->dir;
    ArvAVL* T = no->esq; //auxiliar

    //Faz a rotacao
    no->esq = ptraiz;
    ptraiz->dir = T;

    //calcula as novas altura
    ptraiz->alt = maior(altura_no(ptraiz->esq), altura_no(ptraiz->dir)) +1; 
    no->alt = maior(altura_no(no->dir), altura_no(no->esq)) + 1;
    
    //Retorna nova raiz
    ptraiz = no;
    return no;
}

// Left Right Case
ArvAVL* RotacaoLR(ArvAVL *ptraiz){
    ptraiz->esq = RotacaoRR(ptraiz->esq);
    return RotacaoLL(ptraiz);
}

// Right Left Case
ArvAVL* RotacaoRL(ArvAVL *ptraiz){
    printf("Chegou aqui RL\n");
    ptraiz->dir = RotacaoLL(ptraiz->dir);
    return RotacaoRR(ptraiz);
}

ArvAVL *insere(ArvAVL *ptraiz, int valor){

    //int resultado;
    printf("inserindo => %d .....\n", valor);
    if (ptraiz == NULL){ //caso seja arvore vazia ou nó folha

        ArvAVL* novo;
        novo = (ArvAVL*) malloc(sizeof(ArvAVL));
        if (novo == NULL){printf("ERRO NÃO CONSEGUI ALOCAR  novo tno"); return novo;}
        
        novo->chave = valor;
        novo->alt = 1;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    ArvAVL* atual = ptraiz;
    printf("%d > %d \n", valor, atual->chave);
    if (valor > atual->chave){
        printf("Passou pela comparacao\n");
        atual->dir = insere(atual->dir, valor);
        if (atual->dir){
            printf("Inseriu numero\n");
            int balanco = fator_balanceamento(atual);
            printf("Balancemanento feito\n");
            if (balanco >= 2){
                printf("Passou na comparacao\n");
                if (valor > ptraiz->dir->chave){
                    printf("Entrou na rotacao 1\n");
                    return RotacaoRR(ptraiz);
                    printf("Rotacao Simples feita\n");
                } else {
                    printf("Entrou na rotacao 2\n");
                    return RotacaoRL(ptraiz);
                    printf("Rotacao Dupla feita\n");
                }    
            }
        }
    }
    return ptraiz;
}

int main(int argc, char *argv[]){
    char str[1]; //variavel string do teclado
    int num = 0; //variavel numerica do teclado (ususario)
    printf("comecei\n");
    bool laco = true;
    while(laco){
        if(scanf("%s", str) == 1){
            if(str[0] == 'p'){
                printf("imprimer \n");
                imprime(ptraiz);
                printf("%c\n", str[0]);
                laco = true;
            }
            if(str[0] == 'i'){
                 printf("%c ", str[0]);
                 //lendo espaço                 
                if(scanf("%d", &num) == 1){
                    printf("%d \n",num);            
                    ptraiz = insere(ptraiz, num);
                }
                laco = true;
            }
            if (str[0] == 's'){
                laco = false;
            }
        }
    }
}
