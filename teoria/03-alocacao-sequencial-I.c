#include <stdio.h>
#include <stdlib.h>

//-- AULA 03: Listas Lineares II -- 

/*  Continuando no tema de listas lineares de alocação sequencial, serão vistas as operações elementares de uma
lista: inserção e remoção. Ambas utilizam o procedimento de busca.
    Na inserção, o objetivo é evitar chaves repetidas. Na remoção, o objetivo é localizar o elemento a ser removido.
*/

typedef struct {
    int chave;
    int valor;
} no;

//retorna 0 caso o elemento não se encontra no vetor e retorna a posição caso ele seja encontrado
int busca(no* v, int busc, int tam){
    v[tam].chave = busc;
    int i = 0;
    while(v[i].chave != busc)
        i++;
    if(i != tam)
        return i;
    else
        return 0;
}

//confere se há chaves repetidas, caso insira, retorna o novo número de itens do vetor, senão retorna 0
//caso o vetor esteja cheio, retorna -1
int insere(no* v, no no, int tam, int n){
    if(n < tam){
        if(busca(v, no.chave, tam) == 0){
            v[n+1] = no;
            n++;
            return n;
        }else
            return 0;
    }else
        return -1;
}

//retorna o endereço do nó removido
no* remove(no* v, int rm, int tam, int n){
    int indice;
    no* ret = NULL;
    if(n != 0){
        indice = busca(v, rm, tam);
        if(indice != 0){
            ret = malloc(sizeof(no));
            *ret = v[indice];
            for(int i = indice; i < n-1; i++)
                v[i] = v[i+1];
            return ret;
        }
    }
    return ret;
}

int main(){

    const int TAM = 10;
    no vetor[TAM+1];
    int n = 0; //número de itens no vetor



    return 0;
}
