#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.h"


int leitura(tabela jogadores[], FILE* arq){

    char buffer[128];
    int linha = -1;
    int coluna = 0;

    while(fgets(buffer, 128, arq)){
        coluna = 0;
        linha++;

        if(linha == 0)
            continue;

        char *leitura = strtok(buffer, ",");

        while(leitura){
            switch(coluna){
                case 0:
                jogadores[linha-1].nome = strdup(leitura);
                break;

                case 1:
                jogadores[linha-1].posicao = strdup(leitura);
                break;

                case 2:
                jogadores[linha-1].naturalidade = strdup(leitura);
                break;

                case 3:
                jogadores[linha-1].clube = strdup(leitura);
                break;

                case 4:
                jogadores[linha-1].idade = strdup(leitura);
                break;
            }
            leitura = strtok(NULL, ",");
            coluna++;
        }
    }
    return linha;
}

int main(int argc, char* argv[]){

    //ABERTURA DO ARQUIVO
    FILE* arq = fopen("instancia/jogadores.csv", "r");

    if(!arq){
        printf("Erro! Arquivo não encontrado.\n");
        return -2;
    }

    //PREENCHIMENTO DO STRUCT
    tabela jogadores[1200];

    int linha = leitura(jogadores, arq);

    fclose(arq);

    //IMPRESSÃO DA TABELA ANTES DO ORDENAMENTO
    for(int i = 0; i < linha; i++)
        printf("%s\n", jogadores[i].nome);

    //ORDENAMENTO
    switch(atoi(argv[1])){
        case 1:
        printf("Bubblesort escolhido\n");
        break;

        case 2:
        printf("Quicksort escolhido\n");
        break;

        case 3:
        printf("Radixsort escolhido\n");
        break;

        default:
        printf("Erro! Digite um número de 1 a 3 para escoher o método de ordenação\n");
        return -1;
        break;
    }

    //IMPRESSÃO DA TABELA E INFORMAÇÕES ADICIONAIS
    
    return 0;
}