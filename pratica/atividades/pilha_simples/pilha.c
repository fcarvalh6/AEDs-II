#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h>
#include "pilha.h"


bool ehVazia(no** t) { 
    if(*t == NULL)
        return true;
    else return false;
} 

void push(int v, no** t){ 
    no* n = malloc(sizeof(no)); //cria o nó a ser adicionado
    n -> valor = v; //valor inserido no nó criado
    n -> p = *t; //aponta para o nó abaixo
    *t = n; //t aponta para o topo
} 


int pop(no** t) { 
    if (ehVazia(t)) {
		printf("\nPilha  vazia. Impossível remover elementos");
        return -1; 
    } else {
        no* tmp = *t;
        *t = (*t) -> p;
        return (tmp) -> valor;
    }
} 


int obtem_elemento(no** t) { 
	// Se a pilha estiver vazia, não tem como obter nenhum elemento
    if (ehVazia(t)) {
		printf("\nPilha  vazia. Impossível obter elementos");
        return INT_MIN; 
    }
    // Retorna o elemento do topo da pilha
	return (*t) -> valor; 
} 


int main() { 
    no* topo = NULL; //define o ponteiro do topo
    int n, val;
    do {
        printf("\n************************* MENU ************************");
	    printf("\n1. Push");
	    printf("\n2. Pop");
	    printf("\n3. Obtém elemento");
	    printf("\n4. Pilha vazia?");
	    printf("\n5. Sair");
	    printf("\n Digite sua escolha : ");
	    scanf("%d",&n);
	    switch(n) {
            case 1: 
		        printf("\nDigite o valor ");
                scanf("%d",&val);
                push(val, &topo);
                break;
            case 2: 
                printf("\nElemento retirado : %d",pop(&topo));
                break;
            case 3: 
                printf("\nElemento do topo: %d",obtem_elemento(&topo));
                break;
            case 4: 
                if (ehVazia(&topo)) {
                    printf("\nPilha vazia");
                } else {
                    printf("\nPilha não está vazia");
                }
                break;
            case 5:
                return (1);
                break;
            default: printf("\nOpção errada!");
                break;
        }
	} while(1);
    
    return (0);
 }




