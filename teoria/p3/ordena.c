#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

/*---------BUBBLE SORT----------
*/

void swap(int* xp, int* yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        // Se não houve a troca de elementos
        if (!swapped)
            break;
    }
}

/*----------MERGE SORT-----------
*/


//l é o limite esquerdo, r é o limite direito, m é o meio
//esta função une (merge) duas listas ordenadas 
void merge(int arr[], int l, int m, int r){
    int dimL = m-l+1;//dim é o número de elementos em cada lado
    int dimR = r-m;
    int L[dimL], R[dimR];//cria dois vetores para os elementos em cada lado

    int i, j;
    //preenche os dois vetores com os elementos de cada lado do vetor
    for(i = 0; i < dimL; i++)
        L[i] = arr[l+i];
    for(j = 0; j < dimR; j++)
        R[j] = arr[m+1+j];
    
    i = j = 0;
    int k = l;
    //ordena arr no intervalo passado inserindo os valores dos vetores laterais em ordem
    while(i < dimL && j < dimR){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //insere elementos remanescentes
    while(i < dimL){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < dimR){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r){
    if (l < r) {
        int m = l + (r - l) / 2;

        //repartição da lista
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        //união
        merge(arr, l, m, r);
    }
}

/*----------HEAP SORT-----------
*/

//dada uma subarvore, torná-la uma max-heap
void heapify(int arr[], int n, int i){
    int maior = i;

    //filho a esquerda
    int esq = 2 * i + 1;
    //filho a direita
    int dir = 2 * i + 2;

    if(esq < n && arr[esq] > arr[maior]){
        maior = esq;
    }

    if(dir < n && arr[dir] > arr[maior]){
        maior = dir;
    }

    //a raiz não é o maior.
    //preciso trocar a ordem dos nós, 
    //de modo ao maior ir para a raiz
    if(maior != i){
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;

        //como trocamos os elementos de ordem,
        //preciso garantir que o nó que desceu
        //e que está na posição "maior"
        //é maior do que os seus "novos filhos"

        heapify(arr, n, maior);
    }
}

void heapSort(int arr[], int n){
    //tornar o vetor uma max-heap
    for(int i = n/2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }

    //mover o maior elemento para o final
    for(int i = n-1; i > 0; i--){
        //movendo o maior elemento
        //para o final da heap
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void main(){
    int arr[] = { 66, 30, 27, 13, 25, 10 };
    int n = sizeof(arr) / sizeof(arr[0]);

    //bubbleSort(arr, n);
    mergeSort(arr, 0, n-1);
    // heapSort(arr, n);
    printArray(arr, n);
}