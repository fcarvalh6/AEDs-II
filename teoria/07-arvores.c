#include <stdio.h>
#include <stdlib.h>

/* Árvore é uma estrutura de dados que caracteriza a ordem e
hierarquia entre seus dados.
    Árvores binárias são sstruturas do tipo árvore, onde o grau de cada nó é menor ou
igual a dois.
*/

//Nó de árvore binária
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

/*  Caminhamento: caminhar em uma árvore binária significa percorrer todos os
nós de forma sistemática, de modo que cada nó seja visitado uma vez.
    Usando-se de recursividade, existem 3 formas básicas de caminhamento em árvore binária:
*/

//exemplo de visita
void visita(noA* p){
    printf("%d", p -> valor);
}

//processa o nó, percorre recursivamente, em pré-ordem a subárvore esquerda e depois a direita
void pre_ordem(noA* p){
    visita(p);
    if(p -> esq != NULL) pre_ordem(p -> esq);
    if(p -> dir != NULL) pre_ordem(p -> dir);
}

//percorre recursivamente, em ordem, a subárvore esquerda, processa o nó, percorre a direita
void em_ordem(noA* p){
    if(p -> esq != NULL) em_ordem(p -> esq);
    visita(p);
    if(p -> dir != NULL) em_ordem(p -> dir);
}

//percorre recursivamente, em pós ordem a subárvore esquerda e depois a direita, processa o nó
void pos_ordem(noA* p){
    if(p -> esq != NULL) pos_ordem(p -> esq);
    if(p -> dir != NULL) pos_ordem(p -> dir);
    visita(p);        
}

void main(){
    noA* n1 = alocaNo (2);
    noA* n2 = alocaNo (3);
    noA* n3 = alocaNo (4);
    noA* n4 = alocaNo (5);
    noA* n5 = alocaNo (6);
    noA* n6 = alocaNo (7);
    
    n4 -> esq = n3;
    n3 -> esq = n1;
    n3 -> dir = n2;

    n4 -> dir = n5;
    n5 -> dir = n6;

    noA* raiz = n4;

    pre_ordem(n4);
    printf("\n");
    em_ordem(n4);
    printf("\n");
    pos_ordem(n4);

}
