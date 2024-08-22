#include <stdio.h>
#include <stdlib.h>

//-- AULA 05: Alocação Encadeada I --

/*  De forma geral, o desempenho de algoritmos que implementam operações realizadas em listas com alocação 
sequencial tende a ser bem ruim.
    A alocação encadeada (também conhecida como alocação dinâmica) se caracteriza pela alocação (ou liberação) 
de posições de memória conforme demanda da aplicação.
    Há vantagens e desvantagens associadas a cada tipo de alocação.
    Entretanto, só podem ser precisamente medidas ao se conhecerem as operações envolvidas na aplicação 
desejada.

    De maneira geral pode-se afirmar que a alocação encadeada, apesar de ter um gasto de memória maior em 
virtude da necessidade de um novo campo no nó (o ponteiro para o próximo), é mais conveniente quando o 
problema inclui o tratamento de mais de uma lista.
    Tal fato se aplica tanto à gerência do armazenamento quanto às operações em si, como: juntar listas,
separar listas em sublistas, etc.

    Por outro lado, o acesso ao k-ésimo elemento da lista é imediato em alocação sequencial, enquanto que na 
encadeada obriga ao percurso até o elemento desejado.
    Qualquer estrutura que seja armazenada em alocação encadeada requer o uso de um ponteiro que indique o 
endereço de seu primeiro nó. O percurso da lista é feito então a partir desse ponteiro.
    O algoritmo de busca também é usado para a inserção e remoção.
*/

typedef struct no {
    int chave;
    int valor;
    struct no* prox;
} no;

no* ptlista; //início da lista
no* ant; //anterior e ponteiro para buscas
no* pont;

//assumindo uma lista ordenada, pont será o endereço do nó caso ele seja encontrado e nulo caso contrário
void busca(int busc, no** ant, no** pont){
    *ant = ptlista;
    *pont = NULL;
    no* ptr = (*ptlista).prox;
    while (ptr != NULL){ //o ponteiro do último elemento sempre será NULL
        if((*ptr).chave < busc){
            *ant = ptr;
            ptr = (*ptr).prox;
        } else {
            if((*ptr).chave == busc)
                *pont = ptr;
            ptr = NULL;
        }
    }
}

int insere(no* n){
    int ret = -1;
    busca((*n).chave, &ant, &pont);
    if (pont == NULL){
        (*n).prox = ant -> prox;
        (*ant).prox = n;
        ret = 0;
    }
    return ret;
}

no* rem(int rm){
    no* ret = NULL;
    busca(rm, &ant, &pont);
    if(pont != NULL){
        (*ant).prox = (*pont).prox;
        ret = pont;
    }
    return ret;
}

void imprime(){
    no* ptr = (*ptlista).prox;
    while(ptr != NULL){
        printf("%d\n", (*ptr).chave);
        ptr = (*ptr).prox;
    }
}

void main(){
    ptlista = malloc(sizeof(no)); //aponta para o início da lista
    ptlista -> prox = NULL; //primeiro nó tem como próximo NULL, já que é o único
    ant = ptlista;
    pont = NULL;
    no n1, n2, n3, n4;
    // ptlista -> prox = &n1;
    n1.chave = 1;
    // n1.prox = &n2;
    n2.chave = 2;
    // n2.prox = &n3;
    n3.chave = 4;
    // n3.prox = NULL;
    n4.chave = 3;
    insere(&n1);
    insere(&n2);
    insere(&n3);
    insere(&n4);
    printf("%p\n", pont);
    busca(2, &ant, &pont);
    printf("%p\n", pont);
    printf("%p\n", n1.prox);
    imprime();
    printf("%p\n", rem(2));
    imprime();
}
