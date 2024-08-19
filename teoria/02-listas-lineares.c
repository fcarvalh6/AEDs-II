#include <stdio.h>

//-- AULA 02: Listas Lineares I --

/*  Listas lineares são as estruturas de dados de manipulação
mais simples.
    Uma lista linear agrupa informações referentes a um conjunto
de elementos que, de alguma forma, relacionam entre si.
*/

/*  Uma lista linear é um conjunto de n >= 0 nós no formato L[1], L[2], ..., L[n].
Das posições relativas entre os nós pode-se afirmar que o primeiro nó (caso n > 0) é L[1], e para
1 < k <= n, L[k] é precedido por L[k-1].
*/

/*  Listas lineares possuem três operações básicas: inclusão, remoção e busca. Já que essas operações são
consideradas básicas, é importante que os algoritmos que as implementam sejam eficientes.
*/

//Casos particulares de listas:

/*  PILHA: Inserções e remoções são realizadas somente em um extremo
    FILA: Inserções são realizadas em um extremo e remoções no outro
    DEQUE (double-ended queue): Inserções e remoções são permitidas nas extremidades da lista
*/

/*  O tipo de armazenamento de uma lista linear pode ser classificado de acordo com a posição relativa 
(sempre contígua ou não) na memória.
    O primeiro caso corresponde à alocação sequencial na memória, enquanto o segundo é conhecido como alocação
encadeada.
    ALOCAÇÃO SEQUENCIAL: memória é alocada previamente (não é possível alterá-la), a inserção e remoção não
são feitas de fato (elas são simuladas, como, por exemplo, a posição sendo marcada como pronta para a escrita),
é considerada portanto uma alocação estática.
*/

/*  Seja uma lista linear, cada nó é formado por campos, que armazenam as características distintas dos 
elementos da lista.
    Cada nó possui, geralmente, um identificador, denominado chave.
    Para evitar ambiguidade, assume-se que todas as chaves são distintas.
    Os nós podem se encontrar ordenados, ou não, segundo os valores de suas chaves.
    Assim a lista pode ser ordenada ou não ordenada
*/

typedef struct {
    int chave; //chave única
    int valor; //valor, podendo ser outro struct
} no;

//EXEMPLOS: Busca em de um elemento

const int n = 10;

//-- FUNÇÃO 1 --

no L1[n]; //Seja L1 uma lista de n nós com chaves e valores

int busca1(x){
    int i = 0;
    int busca1 = -1; //se busca1 = -1, o valor não foi encontrado
    while(i < n){ //enquanto a busca estiver dentro do vetor
        if(L1[i].chave == x){
            busca1 = i; //a posição atual é guardada em busca1
            i = n+1; //o loop termina
        }else
            i++; //o contador é incrementado (vai para a próxima posição)
    }
    return busca1;
}

//-- FUNÇÃO 2 --

no L2[n+1]; //Seja L2 uma lista com n+1 nós com chaves e valores

int busca2(x){
    int busca2;
    L2[n].chave = x;
    int i = 0;
    while(L2[i].chave != x && i <= n)
        i++; //obtém a posição da chave buscada
    if(i != n) //confere se o número foi encontrado
        busca2 = i;
        else
            busca2 = -1;
    return busca2;
}

//-- FUNÇÃO 3 (LISTA ORDENADA) --

no L3[n+1]; //Seja L3 uma lista com n+1 nós com chaves em ordem crescente e valores

int buscaord(x){
    int buscaord;
    L3[n].chave = x;
    int i = 0;
    while(L3[i].chave < x && i < n)
        i++;
    if(i == n || L3[i].chave != x)
        buscaord = -1;
        else
            buscaord = i;
    return buscaord;
}

//-- FUNÇÃO 4 (LISTA ORDENADA)

no L4[n]; //Seja L4 uma lista com n nós com chaves em ordem crescente e valores

int buscabin(x){//busca binária (complexidade log na base 2 de n)
    int inf = 0, sup = n-1, buscabin = -1, meio; //inf = limite inferior, sup = limite superior
    while(inf <= sup){
        meio = (inf + sup) / 2;//no início (com n = 10), inf é 0, sup é 9 e meio é 4
        if(L4[meio].chave == x){
            buscabin = meio;
            inf = sup + 1; //para o loop
        }else 
            if(L4[meio].chave < x) //se o meio é menor que x
                inf = meio + 1; //vai para a "metade da frente"
            else
                sup = meio-1; //vai para a metade de baixo
    }
}