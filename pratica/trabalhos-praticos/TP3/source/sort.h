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
void bubbleSort(tabela v[], int n, int *cmp, int *trc);
int reparticao(tabela v[], int inf, int sup);
void quickSort(tabela v[], int inf, int sup);
/*
int encontraMax(int v[], int n);
void radixSort(int v[], int n);
*/

#endif