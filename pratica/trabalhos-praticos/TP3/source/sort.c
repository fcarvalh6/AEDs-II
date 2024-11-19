#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sort.h"

/*TODO:
    -desconsiderar acentos
    -calcular o gasto de memória do bbs
    -adicionar contador na última comparação (?)
*/

void swap(tabela v[], int j, int k){
    tabela tmp = v[j];
    v[j] = v[j+1];
    v[j+1] = tmp;
}

//ordena o vetor por meio do algorimo bubblesort
void bubbleSort(tabela v[], int n, int *cmp, int *trc){
    bool trocou; //registra se houve troca naquela iteração
    for (int i = 0; i < n - 1; i++) { 
        trocou = false; 
        for (int j = 0; j < n - i - 1; j++) {
            *cmp++; //contador de comparações
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {//se v[j] for maior que v[j+1]
                swap(v, j, j+1);
                *trc++; //contador de trocas
                trocou = true;
            }
        }
        if (trocou == false)//TODO: cmp?
            break;
    }
}

//reparte o vetor
int reparticao(tabela v[], int inf, int sup) {
    
    char* pivo = v[sup].nome;//essa função sempre escolhe o último valor como pivô
    
    int i = inf - 1;//i guarda um índice e é iniciado como estando fora do vetor

    for (int j = inf; j <= sup - 1; j++) { //para cada casa do vetor
        if (strcmp(v[j].nome, pivo) < 0) { //joga todos os valores menores para esquerda e os maiores para a direita||| v[j] < pivot
            i++;
            swap(v, i, j);//TODO: descrever melhor indices
        }
    }
    
    swap(v, i+1, sup);//coloca o pivô no meio dos valores ||| &v[i + 1], &v[sup]  
    return i + 1;//retorna a posição do pivô
}

//ordena o vetor por meio do algoritmo quicksort
void quickSort(tabela v[], int inf, int sup) {
    if (inf < sup) {
        
        int ir = reparticao(v, inf, sup);//retorno da função repartição é o índice do pivô

        quickSort(v, inf, ir - 1); //TODO: explicar melhor
        quickSort(v, ir + 1, sup);
    }
}

/*
int encontraMax(int v[], int n) {
    int max = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > max)
            max = v[i];
    return max;
}

//TODO: aportuguesar

//faz countingsort com base no valor representado por exp
void countSort(int v[], int n, int exp) {
    int saida[n]; //vetor de saída
    int count[10] = {0}; //vetor para countingsort iniciado como zero

    // Store count of occurrences in count[]
    for (int i = 0; i < n; i++)
        count[(v[i] / exp) % 10]++;

    // Change count[i] so that count[i] now 
    // contains actual position of this digit
    // in saida[]
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the saida array
    for (int i = n - 1; i >= 0; i--) {
        saida[count[(v[i] / exp) % 10] - 1] = v[i];
        count[(v[i] / exp) % 10]--;
    }

    // Copy the saida vay to v[], 
    // so that v[] now contains sorted 
    // numbers according to current digit
    for (int i = 0; i < n; i++)
        v[i] = saida[i];
}

// The main function to sort v[] of size 
// n using Radix Sort
void radixSort(int v[], int n) {
  
    // Find the maximum number to know 
    // the number of digits
    int m = getMax(v, n); 

    // Do counting sort for every digit
    // exp is 10^i where i is the current 
    // digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(v, n, exp);
}
*/