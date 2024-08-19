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

/*  Filas são estruturas "First in First Out", ou FIFO. Funcionam como uma fila de supermercado, onde o primeiro
elemento adicionado é o primeiro elemento a ser removido.
    Para implementar esta estrutura, é necessário fazer uso de duas variáveis, uma guardando a posição da "frente"
da fila, a outra guardando a posição de "trás". Para remover a necessidade de sempre passar os elementos para frente
toda vez que há uma inserção, muitas filas são implementadas de maneira circular. Ou seja, depois que a parte de trás
da fila chega no final do vetor e ainda houverem espaços na frente (provenientes de remoções), os itens começam a ser
inseridos no início, fazendo assim um "círculo."
    Para a adição de um elemento, move-se o ponteiro r (retaguarda, a parte de trás da fila).
    Para a remoção de um elemento move-se o ponteiro f (frente).
    A situação de fila vazia será representada por f = r = -1.
*/

no fila[M];
int f = -1, r = -1;

//FUNÇÃO DE INSERÇÃO | retorna -1 no caso de fila cheia e a posição de inserção caso contrário
int inseref(no n){
    int ret = -1; //valor de retorno iniciado como -1
    int temp = (r + 1) % M; //variável temporária armazena a próxima posição da fila
    if(temp != f){ //se a próxima posição não estiver ocupada (se não for o início da fila)
        r = temp; //nova retaguarda = próxima posição
        fila[r] = n; //nó adicionado na posição vazia
        ret = r; //retorna a posição do nó
        if(f == -1) //se esta for a primeira inserção da fila
            f = 0; //inicia o valor de f (antes -1)
    }
    return ret;
}

//FUNÇÃO DE REMOÇÃO | retorna nulo no caso de lista vazia e o nó removido caso contrário
no* remove(){
    no* ret = NULL; //inicia ret como NULL
    if(f != -1){ //se a fila não estiver vazia
        ret = malloc(sizeof(no)); //reserva uma porção da memória (endereço guardado em ret)
        *ret = fila[f]; //coloca o nó a ser retirado na porção apontada por ret
        if(f == r) //se a fila estiver vazia após a remoção
            f = r = -1; //define os valores de r e f como os de fila vazia
            else f = (f + 1) % M; //senão, f é a próxima posição
    }
    return ret;
}

