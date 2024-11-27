#ifndef SORT_H
#define SORT_H 

typedef struct tabela_ {
    char* nome;
    char* posicao;
    char* naturalidade;
    char* clube;
    char* idade;
} tabela;

void swap(tabela v[], int j, int k);
void bubbleSort(tabela v[], int n, int *cmp, int *trc, long unsigned int *mem);
int reparticao(tabela v[], int inf, int sup, int *cmp, int *trc, long unsigned int *mem);
void quickSort(tabela v[], int inf, int sup, int *cmp, int *trc, long unsigned int *mem);
void bucketSort(tabela *v, int n, int *cmp, int *trc, unsigned long int *mem);

#endif