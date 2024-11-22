#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "sort.h"

/*TODO:
    -desconsiderar acentos
    -calcular o gasto de memória do bbs
    -adicionar contador na última comparação (?)
    -aportuguesar
*/

/*FUNÇÕES DE UTILIDADE
    -as funções de utilidade são funções gerais que são usadas por dois ou mais algoritmos
    -elas não são relacionadas à forma de ordenamento em si, são apenas auxiliares:
        -tiraAcento e cmpNorm são usadas para desconsiderar acentos ao realizar comparações
        -swap é usada para trocar dois itens de lugar (usada pelo bubbleSort e o quickSort)
*/

char tiraAcento(const char *letra) {

    if ((unsigned char)*letra == 0xC4) {
        // Check second byte for İ
        if ((unsigned char)*(letra + 1) == 0xB0)
            return 'I';
    }

    switch((unsigned char)*letra) {
        // Lowercase accented
        case 0xE1: case 0xE0: case 0xE2: case 0xE3: case 0xE4: return 'a';
        case 0xE9: case 0xE8: case 0xEA: case 0xEB: return 'e';
        case 0xED: case 0xEC: case 0xEE: case 0xEF: return 'i';
        case 0xF3: case 0xF2: case 0xF4: case 0xF5: case 0xF6: return 'o';
        case 0xFA: case 0xF9: case 0xFB: case 0xFC: return 'u';
        case 0xF1: return 'n'; // ñ
        case 0xE7: return 'c'; // ç

        // Uppercase accented
        case 0xC1: case 0xC0: case 0xC2: case 0xC3: case 0xC4: return 'A';
        case 0xC9: case 0xC8: case 0xCA: case 0xCB: return 'E';
        case 0xCD: case 0xCC: case 0xCE: case 0xCF: return 'I';
        case 0xD3: case 0xD2: case 0xD4: case 0xD5: case 0xD6: return 'O';
        case 0xDA: case 0xD9: case 0xDB: case 0xDC: return 'U';
        case 0xD1: return 'N'; // Ñ
        case 0xC7: return 'C'; // Ç

        default: return *letra;
    }
}

int cmpNorm(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        char c1 = tiraAcento(str1);
        char c2 = tiraAcento(str2);
        
        if (c1 != c2) 
            return c1 - c2;
        
        str1++;
        str2++;
    }
    
    return *str1 - *str2;
}

void swap(tabela v[], int j, int k){
    tabela tmp = v[j];
    v[j] = v[k];
    v[k] = tmp;
}

/*BUBBLE SORT
    O algoritmo simples escolhido foi o bubbleSort, ele percorre o vetor realizando comparações
    para garantir que, para cada dupla, o maior valor sempre esteja à direita. Dessa forma os valores
    maiores sobem ao topo como "bolhas."
    TODO: conferir o funcionamento do algo (pra baixo?)
*/

//ordena o vetor por meio do algorimo bubblesort
void bubbleSort(tabela v[], int n, int *cmp, int *trc, long unsigned int *mem){

    (*mem) += sizeof(bool);//contador de gasto de memória
    bool trocou;//registra se houve troca naquela iteração

    (*mem) += sizeof(int);//referente à variável de índice
    for (int i = 0; i < n - 1; i++) {

        trocou = false;//no início da iteração o valor é definido como falso
        for (int j = 0; j < n - i - 1; j++) {

            (*cmp)++;//contador de comparações
            if (cmpNorm(v[j].nome, v[j+1].nome) > 0) {//se v[j] for maior que v[j+1]

                swap(v, j, j+1);//troca os valores, colocando o maior à direita
                (*trc)++;//contador de trocas
                trocou = true;//houve troca
            }
        }
        (*cmp)++;
        if (trocou == false)
            break;//se não houve nenhuma troca, o vetor já está ordenado
    }
    (*mem) += sizeof(tabela);//referente à variável tmp dentro do swap (AAAAAAAAAAAAAAAAAAAAAAAAAAAA)
}

/*QUICK SORT
    O algoritmo ótimo escolhido foi o quickSort. Ele usa o método de dividir por conquistar e
    portanto é mais rápido na média que o bubbleSort. 
    -reparticao divide o vetor, escolhendo um pivô e colocando todos os valores menores à esquerda
    e todos os valores maiores à direita. A repartição ocorre até o último caso (vetor com um item)
    assim garantindo que ele está ordenado. 
    -quicksort realiza a repartição
*/

//reparte o vetor
int reparticao(tabela v[], int inf, int sup, int *cmp, int *trc, long unsigned int *mem) {
    
    (*mem) += sizeof(v[sup].nome);
    char* pivo = v[sup].nome;//essa função sempre escolhe o último valor como pivô
    
    int i = inf - 1;//i guarda um índice e é iniciado como estando fora do vetor

    for (int j = inf; j <= sup - 1; j++) { //para cada casa do vetor
        if (cmpNorm(v[j].nome, pivo) < 0) { //joga todos os valores menores para esquerda e os maiores para a direita
            i++;
            swap(v, i, j);//TODO: descrever melhor indices
        }
    }
    
    swap(v, i+1, sup);//coloca o pivô no meio dos valores 
    return i + 1;//retorna a posição do pivô
}

//ordena o vetor por meio do algoritmo quicksort
void quickSort(tabela v[], int inf, int sup, int *cmp, int *trc, long unsigned int *mem) {
    if (inf < sup) {
        
        int ir = reparticao(v, inf, sup, cmp, trc, mem);//retorno da função repartição é o índice do pivô

        quickSort(v, inf, ir - 1, cmp, trc, mem);//separa o vetor à esquerda do pivô
        quickSort(v, ir + 1, sup, cmp, trc, mem);//separa o vetor à direita do pivô
    }
}

/*RADIX SORT

*/

//Encontra o tamanho máximo de nome na tabela
int nomeMax(tabela tab[], int n) {
    int max = 0;//guarda o tamanho máximo do nome
    for (int i = 0; i < n; i++) {//para cada casa da tabela
        int tam = strlen(tab[i].nome);//tamanho do nome do índice analisado
        if (tam > max) {//se o tamanho do índice analisado for maior que o máximo
            max = tam;//este é o novo máximo
        }
    }
    return max;//retorna o tamanho máximo do nome
}

//counting sort é usado para ordenar os caracteres na posição pos
void countingSortByNome(tabela v[], int n, int pos) {

    int count[256] = {0}; //vetor para contar os valores ASCII
    tabela* output = malloc(n * sizeof(tabela)); //tabela criada para a saída da função

    //conta quantas vezes os caracteres aparecem na posição pos em cada nome
    for (int i = 0; i < n; i++) {//para todas as casas da tabela passada
        //se a posição for menor que o tamanho do nome, o nome possui caracter naquela posição
        char c = pos < strlen(v[i].nome) ? tiraAcento(&v[i].nome[pos]) : 0;//se a condição é verdadeira, c é o caracter, senão é 0 (caso de nome menor)
        count[(unsigned char)c]++;//conta a ocorrência desse caracter
    }

    // Compute cumulative counts
    for (int i = 1; i < 256; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        char c = pos < strlen(v[i].nome) ? tiraAcento(&v[i].nome[pos]) : 0;
        output[--count[(unsigned char)c]] = v[i];
    }

    // Copy the sorted data back to the original array
    for (int i = 0; i < n; i++) {
        v[i] = output[i];
    }

    free(output);
}

// Radix Sort implementation
void radixSort(tabela tab[], int n) {
    int maxLen = nomeMax(tab, n);

    // Perform counting sort for each character position from right to left
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        countingSortByNome(tab, n, pos);
    }
}