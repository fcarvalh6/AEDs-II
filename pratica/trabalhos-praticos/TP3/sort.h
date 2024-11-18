#ifndef SORT.H
#define SORT.H 

typedef struct tabela_ {
    char* nome;
    char* posicao;
    char* naturalidade;
    char* clube;
    char* idade;
} tabela;

//TODO: adicionar variáveis 
void bubbleSort(int v[], int n, int *cmp, int *trc);
int reparticao(int v[], int inf, int sup);
void quickSort(int v[], int inf, int sup);
int encontraMax(int v[], int n);
void radixSort(int v[], int n);

#endif 
