#include <stdio.h>
#include <stdlib.h>

typedef struct no_ {
    int chave;
    int valor;
    struct no_* prox;
} no;

void buscacir(int x, no** ant, no** pont, no* ptlista){
    *ant = ptlista;
    ptlista -> chave = x;
    *pont = ptlista -> prox;
    while((**pont).chave < x){
        *ant = *pont;
        *pont = (**pont).prox;
    }
    if(*pont != ptlista && (**pont).chave == x)
        printf("chave localizada\n");
    else printf("chave não localizada\n");
}

void main(){

}
