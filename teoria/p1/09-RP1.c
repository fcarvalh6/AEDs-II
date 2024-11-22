#include <stdio.h>
#include <stdlib.h>

typedef struct no_ {
    int chave;
    int valor;
    struct no_* ant;
    struct no_* prox;
} no;

//retorna o endereço do nó caso ele se encontre, caso contrário retorna o endereço do próximo
no* buscadup(int x, no* ptlista){
    no* ultimo = ptlista -> ant; //ultimo guarda o endereço do último nó
    if(x <= ultimo -> chave){ //se o último nó for menor que x, isso significa que x não está na lista e deve ser adicionado no final
        no* pont = ptlista -> prox; //pont será usado para percorrer o vetor
        while(pont -> chave < x) //enquanto a chave for menor que x
            pont = pont -> prox; //vai pro próximo
        return pont; //pont será ou o endereço do nó, ou o endereço do próximo
    } else return ptlista; //se a lista estiver vazia ou o nó precisar ser colocado na última posição
}

//insere o nó
void inseredup(int x, int info, no* ptlista){
    no* pont = buscadup(x, ptlista);
    if(pont == ptlista || pont -> chave != x){
        no* anterior = pont -> ant;
        no* pt = malloc(sizeof(no));
        pt -> valor = info;
        pt -> chave = x;
        pt -> ant = anterior;
        pt -> prox = pont;
        anterior -> prox = pt;
        pont -> ant = pt;
    } else printf("O elemento já se encontra na lista!\n");
}

int removedup(int x, no* ptlista){
    no* pont = buscadup(x, ptlista);
    if(pont != ptlista && pont -> chave == x){
        no* anterior = pont -> ant;
        no* posterior = pont -> prox;
        anterior -> prox = posterior;
        posterior -> ant = anterior;
        int valor_recuperado = pont -> valor;
        free(pont);
        return valor_recuperado;
    }
}

void printadup(no* ptlista){
    no* pt = ptlista -> prox;
    while(pt != ptlista){
        printf("chave: %d, valor: %d\n", pt -> chave, pt -> valor);
        pt = pt -> prox;
    }
}

void main(){
    no* ptlista = malloc(sizeof(no));
    ptlista -> prox = ptlista;
    ptlista -> ant = ptlista;
    inseredup(1, 12, ptlista);
    inseredup(2, 15, ptlista);
    inseredup(5, 19, ptlista);
    inseredup(3, 13, ptlista);
    printadup(ptlista);
    printf("valor removido: %d\n", removedup(2, ptlista));
    printadup(ptlista);
}