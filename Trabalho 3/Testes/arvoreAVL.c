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

int fator_balanceamento(ArvAVL *no){
    return labs(altura_no(no->esq) - altura_no(no->dir));
}

void imprime(ArvAVL *ptraiz){
    if (ptraiz != NULL){
        imprime(ptraiz->esq);
        printf("%i(%i)\n",ptraiz->chave, altura_no(ptraiz));
        imprime(ptraiz->dir);
    }
}

ArvAVL* RotacaoRR(ArvAVL *ptraiz){ //ptraiz e o nó que se quer balancear
    ArvAVL* no = ptraiz->esq;
    ArvAVL* T = no->dir; //auxiliar
     
    //Faz a rotaçao
    no->dir = ptraiz;
    ptraiz->esq = T;

    //os dois codigos seguintes calcula as novas altura
    ptraiz->alt = maior(altura_no(ptraiz->esq), altura_no(ptraiz->dir) + 1);
    no->alt = maior(altura_no(no->esq), ptraiz->alt) + 1;
    ptraiz = no;
    return no;
}

ArvAVL* RotacaoLR(ArvAVL *ptraiz){
    ptraiz->esq = RotacaoSE(ptraiz->esq);
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
    printf("valor > atual->chave \n");
    printf("%d > %d \n", valor, atual->chave);
    if (valor > atual->chave){
        printf("direta\n");
        atual->dir = insere(atual->dir, valor);
        if (atual->dir){
            int balanco = fator_balanceamento(atual);
            if (balanco >= 2){
                if (ptraiz->dir->chave > valor){
                    return RotacaoRR(ptraiz);
                } else {
                    return RotacaoLR(ptraiz);
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
    while(!feof(stdin)){
        if(scanf("%s", str) == 1){
            if(str[0] == 'p'){
                printf("imprimer \n");
                imprime(ptraiz);
                printf("%c\n", str[0]);
            }
            if(str[0] == 'i'){
                 printf("%c ", str[0]);
                 //lendo espaço                 
                if(scanf("%d", &num) == 1){
                    printf("%d \n",num);            
                    ptraiz=insere(ptraiz, num);
                }
            }
        }
    }
    return 0;
}
