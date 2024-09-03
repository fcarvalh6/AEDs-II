#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE* arq;
    arq = fopen("labirintos/labirinto1.txt", "r");

    if(arq == NULL){
        printf("ERRO! Arquivo não foi encontrado!\n");
        return 1;
    }

    const int TAM = 10;
    char labirinto[TAM][TAM];
    char aux;

    for(int i = 0; i < TAM; i++)
        for(int j = 0; j < TAM; j++){
            aux = fgetc(arq);
            if(aux == 10)
                aux = fgetc(arq);
            labirinto[i][j] = aux;
        }

    for(int i = 0; i < TAM; i++){
        for(int j = 0; j < TAM; j++)
            printf("%c", labirinto[i][j]);
        printf("\n");
    }
    
    return 0;
}