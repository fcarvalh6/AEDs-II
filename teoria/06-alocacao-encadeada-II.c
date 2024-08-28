#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int chave;
    int valor;
    struct no* prox;
} no;

void insere_pilha(no* n, no** t){
    n -> prox = *t;
    *t = n;
}

no* remove_pilha(no** t){
    if(*t != NULL){
        no* ret = *t;
        *t = (**t).prox;
        return ret;
    }
    return NULL;
}

void imprime_pilha(no* t){
    while(t != NULL){
        printf("%d\n", t -> chave);
        t = t -> prox;
    }
}

void insere_lista(no* n, no** i, no** f){
    if(*f != NULL)
        (**f).prox = n;
    else *i = n;
    *f = n;
}

no* remove_fila(no** i, no** f){
    if(*i != NULL){
        no* ret = *i;
        *i = (**i).prox;
        return ret;
        if(*i = NULL)
            *f = NULL;
    }
    return NULL;
}

void imprime_fila(no* i, no* f){
    while(i != NULL){
        printf("%d\n", i -> chave);
        i = i -> prox;
    }
}

void menu(){
    printf("#####--------------#####\n");
    printf("---ALOCAÇÃO ENCADEADA---\n");
    printf("#####--------------#####\n\n");
    printf("Escolha a operação desejada:\n");
    printf("(1) Criação (2) Impressão (3) Edição (4) Busca (0) SAIR");
}

void main(){
    no* topo = NULL;
    no* inicio = NULL;
    no* fim = NULL;
    no* n1 = malloc(sizeof(no));
    n1 -> chave = 2;
    n1 -> prox = NULL;
    no* n2 = malloc(sizeof(no));
    n2 -> chave = 3;
    n2 -> prox = NULL;
    insere_lista(n1, &inicio, &fim);
    insere_lista(n2, &inicio, &fim);
    remove_fila(&inicio, &fim);
    imprime_fila(inicio, fim);
    menu();
}
