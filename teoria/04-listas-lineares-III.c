#include <stdio.h>
#include <stdlib.h>

/*  O armazenamento sequencial de listas é empregado, normalmente, quando as estruturas sofrem poucas alterações
ao longo do tempo. Também é empregado em casos particulares de listas.
    Nesse caso, a situação favorável é aquela em que inserções e remoções não acarretam movimentação de nós, tais
como DEQUES, PILHAS e FILAS.
*/

/*  Pilhas são estruturas "Last In First Out", ou LIFO, funcionam como uma pilha de livros ou pratos, onde ao
colocar um novo item ele vai ao topo e o primeiro item a ser retirado é o do topo.
    A implementação em código deste tipo de estrutura tem como principal característica o armazenamento da posi-
ção do topo, pois é nesta posição que são feitas as adições e remoções.
*/

//como anteriormente, serão usados nós com chaves únicas e que armazenam valores
typedef struct no {
    int chave;
    int valor;
} no;

//são definidas duas variáveis globais, o topo da lista (t) e o tamanho máximo (M)
const int M = 10;
int t = -1; //t sempre marcará a posição do item que está no topo da lista, inicia com -1, após a primeira inserção passa pra 0
no pilha[M];

//FUNÇÃO DE INSERÇÃO | retorna -1 no caso de pilha cheia; se não, o novo tamanho da lista
int insere(no n){
    if(t != M-1){//confere se há espaço na pilha
        t++;
        pilha[t] = n;
        return t;
    }
    return -1;
}

//FUNÇÃO DE REMOÇÃO | retorna NULL no caso de pilha vazia; se não, o elemento do topo 
no* remove(){
    no* ret = NULL;
    if(t != -1){
        ret = malloc(sizeof(no));
        *ret = pilha[t];
        t--;
        return ret;
    }
    return ret;
}