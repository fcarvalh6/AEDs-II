#ifndef SORT_H
#define SORT_H 

typedef struct tabela_ {
    char* nome;
    char* posicao;
    char* naturalidade;
    char* clube;
    char* idade;
} tabela;

/*TODO:
    -adicionar variáveis
    -contadores qsort
*/

void swap(tabela v[], int j, int k);
void bubbleSort(tabela v[], int n, int *cmp, int *trc, long unsigned int *mem);
int reparticao(tabela v[], int inf, int sup, int *cmp, int *trc, long unsigned int *mem);
void quickSort(tabela v[], int inf, int sup, int *cmp, int *trc, long unsigned int *mem);
int encontraMax(int v[], int n);
void radixSort(tabela* arr, int n);


#endif