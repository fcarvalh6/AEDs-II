#include <stdio.h>

void imprime(int v[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }
}

int main(){
//-- AULA 1: Introdução à Complexidade de Algoritmos --

/*  Duas características de um algoritmo são importantes: tempo de execução e quantidade de memória utilizada
* essas características serão avaliadas em função de uma variável (por exemplo, seja n o tamanho de um vetor,
* a complexidade sera c(n), onde c é uma função de complexidade que será vista em breve).
*/

//EXEMPLO 1: Complexidade de um algoritmo simples
    const int n1 = 10;//n1 é o tamanho do vetor
    int v1[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int lim1 = n1/2, temp;
    for(int i = 0; i < lim1; i++){
        temp = v1[i];
        v1[i] = v1[n1-1-i];
        v1[n1-1-i] = temp;
    }
    imprime(v1, n1);

/*  Para o algoritmo acima, a complexidade de espaço é 4 + n (considerando as 4 variáveis, lim, temp, i e n)
*   A complexidade de tempo pode ser dada de maneira analítica, observando o número de comandos de atribuição,
* tanto antes quanto dentro da repetição. 
*   A conta é feita da seguinte maneira: 2 [lim e n] + 4 [número de atribuições dentro do loop] * (n/2) [número de repetições]
* esta conta pode ser simplificada, obtendo assim a complexidade de 2 + 2*n
*/

//EXEMPLO 2: Algoritmo alternativo
    int n2 = 10;
    int v2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int lim2 = n2;
    int v3[n2];
    for(int i = 0; i < lim2; i++)
        v3[i] = v2[n2-i-1];
    imprime(v3, n2);

/*  O algoritmo acima cumpre a mesma função de inverter o vetor, suas complexidades, porém, são diferentes.
* Complexidade de espaço: 2 [lim e i] + 2*n [dois vetores de tamanho n]
* Complexidade de tempo: 1 + 2*n 
*/

/*  Já que encontrar a complexidade de um algoritmo não é simples, algumas simplificações serão feitas (dado
* que a quantidade dos dados manipulados seja suficientemente grande). Constantes aditivas ou multiplicativas
* não serão consideradas.
*   No caso dos exemplos anteriores, são feitas as seguintes simplificações: 
* 4 + n -> n ; 2 + 2*n -> n
* 2 + 2*n -> n ; 1 + 2*n -> n
*   Desta forma, uma soma de matrizes terá (normalmente) complexidade de tempo n², pois as matrizes possuem
* duas dimensões, esta é uma característica inerente do problema! Uma multiplicação de matrizes soma uma dimensão,
* a complexidade sendo (normalmente) n³.
*/

/*  As complexidades serão divididas em três casos notáveis: a complexidade do melhor caso (Ômega), pior caso (O) e caso médio (Theta)
* A complexidade de pior caso (O) acaba sendo a mais importante, já que define um limite superior para o número de operações.
* Por este motivo, o termo "complexidade" é normalmente usado ao se referir à complexidade de pior caso.
*/

/*  Já que a notação O se preocupa principalmente com o comportamento asintótico da função de complexidade por n,
* termos com graus menores do que o maior grau podem ser desconsiderados.
*/
}