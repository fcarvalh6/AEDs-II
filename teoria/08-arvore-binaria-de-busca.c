#include <stdio.h>
#include <stdlib.h>

typedef struct noA_ {
    int valor;
    struct noA_* esq;
    struct noA_* dir;
} noA;

noA* alocaNo(int v){
    noA* n = malloc(sizeof(noA));
    n -> esq = NULL;
    n -> dir = NULL;
    n -> valor = v;
    return n;
}

noA* insere(noA* raiz, noA * n){
    if(raiz == NULL) return n;
    if(raiz -> valor > n -> valor)
        raiz -> esq = insere(raiz -> esq, n);
    else
        raiz -> dir = insere(raiz -> dir, n);
    return raiz;
}

noA* busca(noA* raiz, int v){
    if(raiz == NULL || raiz -> valor == v) return raiz;
    if(raiz -> valor > v) return busca(raiz -> esq, v);
    else return busca(raiz -> dir, v);
}

void main(){
    noA* raiz = NULL;
    int op = -1;

    //5 4 7 2 3 6 8 9 
    while(op != 0){
        printf("Insira o valor (0 para sair): ");
        scanf("%d", &op);
        if(op != 0) insere(raiz, alocaNo(op)); //pode melhorar
    }

    
}