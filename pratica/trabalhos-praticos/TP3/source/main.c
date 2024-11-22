#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

/*TRABALHO PRÁTICO 3 - AEDs II

    Este trabalho é um comparatório entre algoritmos de ordenação de trẽs tipos:
    simples, ótimos e em tempo linear. Um arquivo .csv com informações de jogadores
    é lido e a ordenação é feita em ordem alfabética. Há uma impressão antes e depois
    do ordenamento. Além disso, o número de comparações, trocas e o gasto da memória
    são registrados e informados ao final da execução.

    As funções de ordenação estão no arquivo sort.c. Descrições dos valores de erro 
    e das diferentes etapas do código encontram-se abaixo, em comentários como este. 

    Autores: Filipe Carvalho e Jeann Batista
*/

//realiza a leitura, guardando cada campo no struct tabela; retorna o número de linhas
int leitura(tabela tab[], FILE* arq, int max){

    char buffer[128];//bufffer usado para guardar a linha lida
    int linha = -2;//número da linha do struct que receberá os dados
    int coluna = 0;//número da coluna da tabela que está sendo lida

    while(fgets(buffer, 128, arq) && linha < max){//enquanto houverem linhas para serem lidas no arquivo

        coluna = 0;//coluna é zerada no começo de cada nova linha
        linha++;//nova linha é registrada

        if(linha == -1)//no caso da primeira linha do arquivo
            continue;//pula para não ler o cabeçalho

        char *leitura = strtok(buffer, ",");//buffer guarda a linha, strtok separa a string pelas vírgulas

        while(leitura){//enquanto houverem colunas a serem lidas

            switch(coluna){//cada número de coluna corresponde a um campo do struct

                case 0:
                tab[linha].nome = strdup(leitura);//strdup duplica o conteúdo e retorna o ponteiro
                break;

                case 1:
                tab[linha].posicao = strdup(leitura);
                break;

                case 2:
                tab[linha].naturalidade = strdup(leitura);
                break;

                case 3:
                tab[linha].clube = strdup(leitura);
                break;

                case 4:
                tab[linha].idade = strdup(leitura);
                break;
            }
            leitura = strtok(NULL, ",");//a próxima coluna (se houver) é colocada em leitura
            coluna++;

        }
    }
    return linha+1;//linha é o último índice do struct, linha+1 é o número de linhas
}

//imprime a tabela; l é o número de linhas da tabela v
void printa(tabela v[], int l){
    printf("Nome, Posição, Naturalidade, Clube, Idade\n");//cabeçalho
    for(int i = 0; i < l; i++)
        printf("%d - %s, %s, %s, %s, %s", (i+1), v[i].nome, v[i].posicao,
                                             v[i].naturalidade, v[i].clube, v[i].idade);
}

/*ERROS:
    -1 = arquivo não encontrado
    -2 = erro com os argumentos passados
*/

int main(int argc, char* argv[]){

    /*ABERTURA DO ARQUIVO
        -confere se o arquivo foi encontrado
        -confere se os argumentos foram passados de forma correta
    */

    FILE* arq = fopen("./instancia/jogadores.csv", "r");//abre o arquivo na pasta de instâncias no modo de leitura

    if(!arq){//se o arquivo não tiver sido encontrado
        printf("Erro! Arquivo não encontrado.\n");
        return -1;//retorna erro
    }

    int alg;//guarda o algoritmo escolhido (1 = bubble, 2 = quick, 3 = radix)
    if(argc == 2){//confere se o número correto de argumentos foi passado

        alg = atoi(argv[1]);//argv[1] é a seleção de algoritmo e deve ser um int
        if(alg < 1 || alg > 3){//deve também estar entre 1 e 3
            printf("Erro! Número inteiro entre 1 e 3 não foi passado como argumento.\n");
            return -2;
        }

    }else{

        printf("Erro! Número incorreto de argumentos.\n");
        return -2;

    }

    /*PREENCHIMENTO DA TABELA
        -tabela de jogadores é criada com base no struct em sort.h
        -tabela é preenchida com as informações do arquivo .csv (os acentos foram removidos para padronizar as comparações com o strcmp)
        -o número de linhas é retornado pela função de leitura e guardado (usado como limite superior)
        -depois da leitura ter sido feita, o arquivo já pode ser fechado 
    */

    const int MAX = 1200;//número máximo de linhas
    tabela jogadores[MAX];

    int linha = leitura(jogadores, arq, MAX);//função de leitura

    fclose(arq);//fechamento do arquivo

    /*IMPRESSÃO DA TABELA ANTES DO ORDENAMENTO
    */

    printf("\tTabela de jogadores antes do ordenamento: \n\n");
    printa(jogadores, linha);

    /*ORDENAMENTO
        -as variáveis troca e comp guardam o número de trocas e comparações feitas respectivamente
        -o valor de alg (argv[1]) decide o algoritmo que será usado
        -o ordenamento prossegue por meio do algoritmo escolhido
    */

    int troca = 0, comp = 0;//trocas e comparações feitas durante a execução do arquivo
    long unsigned int mem = 0;//memória ocupada por variáveis geradas durante a execução
    clock_t inicio;

    switch(alg){

        case 1:
        printf("\nBubbleSort escolhido, realizando o ordenamento\n");
        inicio = clock();//horário de início da execução
        bubbleSort(jogadores, linha, &comp, &troca, &mem);
        break;

        case 2:
        printf("\nQuickSort escolhido, realizando o ordenamento\n");
        inicio = clock();//horário de início da execução
        quickSort(jogadores, 0, linha-1, &comp, &troca, &mem);
        break;

        case 3:
        printf("\nRadixSort escolhido, realizando o ordenamento\n");
        inicio = clock();//horário de início da execução
        bucketSort(jogadores, linha);
        break;
    }

    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;//horário de término - horário de início

    /*IMPRESSÃO DA TABELA ORDENADA E INFORMAÇÕES ADICIONAIS
    */
   
    printf("\tTabela de jogadores após o ordenamento: \n\n");
    printa(jogadores, linha);
    
    printf("\nInformações adicionais:\n");
    printf("Tempo de execução: %f\n", tempo);
    printf("Trocas: %d, Comparações: %d\n", troca, comp);
    printf("Gasto de memória: %ld Bytes\n", mem);

    return 0;
}