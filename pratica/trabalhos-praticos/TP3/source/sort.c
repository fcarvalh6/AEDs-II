#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "sort.h"

/*NESTE ARQUIVO 
    -estão contidas todas as funções referentes à ordenação da tabela:
        -bubbleSort
        -quickSort
        -bucketSort
*/

//swap é uma função de utilidade usada para trocar dois itens de posição
void swap(tabela v[], int j, int k){
    tabela tmp = v[j];
    v[j] = v[k];
    v[k] = tmp;
}

/*BUBBLE SORT
    O algoritmo simples escolhido foi o bubbleSort, ele percorre o vetor realizando comparações
    para garantir que, para cada dupla, o maior valor sempre esteja à direita. Dessa forma os valores
    maiores sobem ao topo como "bolhas."
*/

//ordena o vetor por meio do algorimo bubbleSort
void bubbleSort(tabela v[], int n, int *cmp, int *trc, long unsigned int *mem){

    (*mem) += sizeof(bool);//contador de gasto de memória
    bool trocou;//registra se houve troca naquela iteração

    (*mem) += sizeof(int);//referente à variável de índice
    for (int i = 0; i < n - 1; i++) {

        trocou = false;//no início da iteração o valor é definido como falso
        for (int j = 0; j < n - i - 1; j++) {

            (*cmp)++;//contador de comparações
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {//se v[j] for maior que v[j+1]

                (*trc)++;//contador de trocas
                swap(v, j, j+1);//troca os valores, colocando o maior à direita
                trocou = true;//houve troca
            }
        }
        (*cmp)++;
        if (trocou == false)
            break;//se não houve nenhuma troca, o vetor já está ordenado
    }
    (*mem) += sizeof(tabela);//referente à variável tmp dentro do swap
}

/*QUICK SORT
    O algoritmo ótimo escolhido foi o quickSort. Ele usa o método de dividir por conquistar e
    portanto é mais rápido na média que o bubbleSort. 
    -a função reparticao divide o vetor, escolhendo um pivô e colocando todos os valores menores à esquerda
    e todos os valores maiores à direita. A repartição ocorre até o último caso (vetor com um item)
    assim garantindo que ele está ordenado. 
    -a função quickSort realiza a repartição
*/

//reparte o vetor e separa eles em torno do pivô
int reparticao(tabela v[], int inf, int sup, int *cmp, int *trc, long unsigned int *mem) {
    
    (*mem) += sizeof(v[sup].nome);
    char* pivo = v[sup].nome;//essa função sempre escolhe o último valor como pivô
    
    (*mem) += sizeof(int);
    int i = inf - 1;//i guarda um índice e é iniciado como estando fora do vetor

    for (int j = inf; j <= sup - 1; j++) { //para cada casa do vetor
        (*cmp)++;
        if (strcmp(v[j].nome, pivo) < 0) { //joga todos os valores menores para esquerda e os maiores para a direita
            i++;
            (*trc)++;//contador de trocas
            swap(v, i, j);//j é a posição do valor analisado e i é onde esse valor deve ir
        }
    }
    (*trc)++;
    swap(v, i+1, sup);//coloca o pivô no meio dos valores 
    return i + 1;//retorna a posição do pivô
}

//ordena o vetor por meio do algoritmo quickSort
void quickSort(tabela v[], int inf, int sup, int *cmp, int *trc, long unsigned int *mem) {
    (*cmp)++;
    if (inf < sup) {
        
        (*mem)+= sizeof(int);
        int ir = reparticao(v, inf, sup, cmp, trc, mem);//retorno da função repartição é o índice do pivô

        quickSort(v, inf, ir - 1, cmp, trc, mem);//separa o vetor à esquerda do pivô
        quickSort(v, ir + 1, sup, cmp, trc, mem);//separa o vetor à direita do pivô
    }
}

/*BUCKET SORT
    O algoritmo em tempo linear escolhido foi o bucket sort. Ele cria "baldes" para a ordenação,
    separando os nomes pela primeira letra. Após isso, cada balde é ordenado individualmente com
    o quickSort. 
*/

//ordena o vetor por meio do algoritmo bucketSort
void bucketSort(tabela *v, int n, int *cmp, int *trc, unsigned long int *mem) {
    (*mem) += sizeof(int);
    int nBucket = 26;//existem 26 primeiras letras possíveis, então são 26 baldes
    (*mem) += nBucket * sizeof(tabela*);
    tabela **buckets = malloc(nBucket * sizeof(tabela*));//cria um vetor de baldes
    (*mem) += nBucket * sizeof(int);
    int *tamBucket = calloc(nBucket, sizeof(int));//cria um vetor de tamanho dos baldes (preenchido por 0 devido ao calloc)
    
    (*mem) += n * nBucket * sizeof(tabela);
    tabela *espBucket = malloc(n * nBucket * sizeof(tabela));//espaço para todos os elementos de todos os baldes
    for (int i = 0; i < nBucket; i++) {
        buckets[i] = espBucket + i * n;//organiza o espaço para todos os baldes
    }

    for (int i = 0; i < n; i++) {
        (*mem) += sizeof(int) + sizeof(char);
        int iBucket = 0;//índice do balde onde o nome será inserido
        char c = v[i].nome[0];//primeira letra do nome

        /*O condicional abaixo define o índice do balde com base
        na primeira letra do nome
        */
        (*cmp)++;
        if(c >= 'A' && c <= 'Z')
            iBucket = c - 'A';
        else if(c >= 'a' && c <= 'z')
            iBucket = c - 'a';

        /*  -buckets são todos os baldes;
            -iBucket é o índice do balde ao qual o nome será adicionado
            -tamBucket é o índice da última posição do balde
            -v[i] é o nome
        */
        buckets[iBucket][tamBucket[iBucket]++] = v[i];//o nome é adicionado ao balde correto
    }

    (*mem) += sizeof(int);
    int index = 0;//index guarda onde os baldes serão adicionados na tabela final ordenada
    for (int i = 0; i < nBucket; i++) {
        (*cmp)++;
        if (tamBucket[i] > 1) {
            quickSort(buckets[i], 0, tamBucket[i] - 1, cmp, trc, mem);//todos os baldes são ordenados com o quickSort
        }
        memcpy(v + index, buckets[i], tamBucket[i] * sizeof(tabela));//baldes ordenados são copiados na saída
        index += tamBucket[i];//posição de início do próximo balde
    }

    free(espBucket);
    free(buckets);
    free(tamBucket);
}
