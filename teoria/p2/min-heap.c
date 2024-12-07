#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//tamanho do heap
#define HTAM 20

//retorna o pai
int pai(int i){
    return (i-1)/2; //se um nó tem posição i, seu pai tem posição (i-1)/2
}

//retorna o filho esquerdo
int fesq(int i){
    return (2*i)+1; //se um nó tem posição i, seu filho esquerdo tem posição 2*i+1
}

//retorna o filho direito
int fdir(int i){
    return (2*i)+2; //se um nó tem posição i, seu filho direito tem posição 2*i+2
}

//troca o filho de lugar com o pai
void swap(int *filho, int *pai){
    int tmp = *filho; //guarda temporariamente o nó filho
    *filho = *pai; //posição do filho recebe o pai
    *pai = tmp; //posição do pai recebe o filho
}

/* insere o valor passado no heap
   n é a última posição do heap, h é o heap e k é o valor a ser inserido */
void insereheap(int *n, int h[HTAM], int k){

    if(*n == HTAM){ //confere se há espaço no heap 
        printf("Overflow, não foi possível inserir o valor.\n");
        return;
    }

    //insere o valor na última posição do heap
    (*n)++; //ao adicionar um novo valor, a última posição do vetor passa para a seguinte
    int i = (*n) - 1; //i é o índice onde ocorre a inserção (a última posição do heap)
    h[i] = k; //valor é inserido na posição correta

    //ajusta caso necessário (quando a o pai não for menor que o filho, como em todo min-heap)
    while(i != 0 && h[pai(i)] > h[i]){ //enquanto não chegar na raiz do heap e o pai for maior que o filho
        swap(&h[i], &h[pai(i)]); //troca pai com o filho
        i = pai(i); //repete a função com o pai
    }
}

//garante que o valor mínimo está na raiz da subárvore
//i é a raiz da subárvore a ser minimizada, n é a última posição do heap e h é o heap
void minimizar(int i, int n, int h[HTAM]){

    int esq = fesq(i); //guarda a posição do filho esquerdo de i
    int dir = fdir(i); //guarda a posição do filho direito de i
    int min = i; //o valor mínimo é iniciado como i, ele será comparado com seus filhos

    if(esq < n && h[esq] < h[i]) //se o filho estiver dentro das dimensões do heap e for menor que o pai
        min = esq; //o mínimo agora é o esquerdo

    if(dir < n && h[dir] < h[min]) //se o filho estiver dentro das dimensões do heap e for menor que min
        min = dir; //o mínimo agora é o direito

    if(min != i){ //se algum filho tiver sido menor que o pai (quebrando a propriedade de min-heap)
        swap(&h[i], &h[min]); //troca o pai com o mínimo
        minimizar(min, n, h); //chama a função de minimização com o pai (agora filho)
    }
}

//remove a raiz do heap
int removemin(int *n, int h[HTAM]){

    if(*n <= 0) //se o heap estiver vazio
        return INT_MAX; //retorna o valor máximo de int (age como uma mensagem de erro)

    if(*n == 1){ //se só houver um valor no heap
        (*n)--; //a última posição muda para a anterior
        return h[0]; //retorna a raiz
    }

    //se ambas as comparações acima retornaram falso, isso significa que há mais de um valor no heap
    int raiz = h[0]; //raiz é o valor em h[0], que deverá ser retornado
    h[0] = h[(*n) - 1]; //o último valor do heap é enviado para a raiz
    (*n)--; //a última posição muda para a anterior
    minimizar(0, *n, h); //a função de correção é chamada, partindo da raiz
    return raiz; //retorna o valor mínimo
    
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
    printf("%d\n", removemin(&hn, heap));
    printa(heap, hn);
    printf("%d\n", removemin(&hn, heap));
    printa(heap, hn);
    printf("%d\n", removemin(&hn, heap));
    printa(heap, hn);
    printf("%d\n", removemin(&hn, heap));
    printa(heap, hn);
    printf("%d\n", removemin(&hn, heap));

}