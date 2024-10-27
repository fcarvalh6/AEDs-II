#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//tamanho do heap
#define HTAM 20

//retorna o pai
int pai(int i){
    return (i-1)/2;
}

//retorna o filho esquerdo
int fesq(int i){
    return (2*i)+1;
}

//retorna o filho direito
int fdir(int i){
    return (2*i)+2;
}

//troca o filho de lugar com o pai
void swap(int *filho, int *pai){
    int tmp = *filho;
    *filho = *pai;
    *pai = tmp;
}

//garante que o valor máximo está na raiz da subárvore
void maximizar(int i, int n, int h[HTAM]){
    int e = fesq(i);
    int d = fdir(i);
    int max = i;
    if(e < n && h[e] > h[i])
        max = e;
    if(d < n && h[d] > h[max])
        max = d;
    if(max != i){
        swap(&h[i], &h[max]);
        maximizar(max, n, h);
    }
}

//insere o valor passado no heap
void insereheap(int *n, int h[HTAM], int k){
    if(*n == HTAM){
        printf("Overflow, não foi possível inserir o valor.\n");
        return;
    }
    //insere o valor na última posição do heap
    (*n)++;
    int i = (*n) - 1;
    h[i] = k;
    //ajusta caso necessário
    while(i != 0 && h[pai(i)] < h[i]){
        swap(&h[i], &h[pai(i)]);
        i = pai(i);
    }
}

//remove a raiz do heap
int removemax(int *n, int h[HTAM]){
    if(*n <= 0)
        return INT_MIN;
    if(*n == 1){
        (*n)--;
        return h[0];
    }
    int raiz = h[0];
    h[0] = h[(*n) - 1];
    (*n)--;
    maximizar(0, *n, h);
    return raiz;
}

//imprime o heap na tela
void printa(int h[HTAM], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", h[i]);
    }
    printf("\n");
}

void main(){
    int hn = 0;
    int heap[HTAM];
    insereheap(&hn, heap, 4);
    insereheap(&hn, heap, 2);
    insereheap(&hn, heap, 1);
    insereheap(&hn, heap, 3);
    insereheap(&hn, heap, 7);
    printa(heap, hn);
    printf("%d\n", removemax(&hn, heap));
    printa(heap, hn);
    printf("%d\n", removemax(&hn, heap));
    printa(heap, hn);
    printf("%d\n", removemax(&hn, heap));
    printa(heap, hn);
    printf("%d\n", removemax(&hn, heap));
    printa(heap, hn);
    printf("%d\n", removemax(&hn, heap));

}