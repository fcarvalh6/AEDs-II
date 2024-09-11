#include <stdio.h>
#include <stdlib.h>

typedef struct no_ {
    int x;
    int y;
    struct no_* prox;
} no;

//Função de leitura de labirinto. Recebe endereço do labirinto e o imprime.
void printlab(char L[10][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            printf("%c", L[i][j]);
        printf("\n");
    }
}

void printpilha(no* t){
    while(t != NULL){
        printf("%d, %d\n", t -> x, t -> y);
        t = t -> prox;
    }
}

void push(int xn, int yn, no** t){ 
    no* n = malloc(sizeof(no)); //cria o nó a ser adicionado
    n -> x = xn; //insere o valor de x
    n -> y = yn; //insere o valor de y
    n -> prox = *t; //aponta para o item abaixo
    *t = n;//t aponta para o topo
}

no* pop(no** t){
    if(*t != NULL){
        no* tmp = *t;
        *t = (**t).prox;
        return tmp;
    } else return NULL;
}

int main(){

    //LEITURA
    FILE* arq = fopen("labirintos/labirinto3.txt", "r");
    
    if(arq == NULL){
        printf("ERRO! Arquivo não foi encontrado!\n");
        return 1;
    }
    
    char lab[10][10];

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            lab[i][j] = fgetc(arq);
        fgetc(arq); //descarta os newlines
    }    
    
    fclose(arq);

    //PRIMEIRA IMPRESSÃO
    printlab(lab);

    //ESTRUTURAS DE DADOS
    no* cam = NULL;//pilha onde será guardado o caminho percorrido
    no* bif = NULL;

    //ENCONTRA A SAÍDA
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(lab[i][j] == 69){
                push(i, j, &cam);
            }

    // no* tmp = pop(&cam);
    // printf("%d %d\n", tmp -> x, tmp -> y);

    int saida = 1;
    int conta;
    int sonda;
    no* tmp;

    while(saida == 1){
        conta = 0;
        int xa = cam -> x;
        int ya = cam -> y;

        if(xa > 0){
            sonda = lab[xa-1][ya];//CIMA

            switch(sonda){
                case 48://ZERO
                push(xa-1, ya, &bif);
                conta++;
                break;
                case 83://S
                push(xa-1, ya, &cam);
                saida = 0;
                break;
            }
        }

        if(ya > 0){
            sonda = lab[xa][ya-1];//ESQUERDA

            switch(sonda){
                case 48://ZERO
                push(xa, ya-1, &bif);
                conta++;
                break;
                case 83://S
                push(xa, ya-1, &cam);
                saida = 0;
                break;
            }
        }

        if(xa < 9){
            sonda = lab[xa+1][ya];//BAIXO

            switch(sonda){
                case 48://ZERO
                push(xa+1, ya, &bif);
                conta++;
                break;
                case 83://S
                push(xa+1, ya, &cam);
                saida = 0;
                break;
            }
        }

        if(ya < 9){
            sonda = lab[xa][ya+1];//DIREITA

            switch(sonda){
                case 48://ZERO
                push(xa, ya+1, &bif);
                conta++;
                break;
                case 83://S
                push(xa, ya+1, &cam);
                saida = 0;
                break;
            }
        }

        switch(conta){
            case 1:
            lab[xa][ya] = 67;//C
            tmp = pop(&bif);//pega o primeiro da pilha de bifurcações e guarda na pilha de caminho (próximo a ser acessado)
            push(tmp -> x, tmp -> y, &cam);//
            break;

            case 2:
            lab[xa][ya] = 67;//C
            tmp = pop(&bif);//pega o primeiro da pilha de bifurcações e guarda na pilha de caminho (próximo a ser acessado)
            push(tmp -> x, tmp -> y, &cam);
            push(xa, ya, &bif);//guarda a posição onde ocorreu a bifurcação
            break;

            case 0:
            while(cam -> x != bif -> x || cam -> y != bif -> y)//volta até a bifurcação anterior
                pop(&cam);
            pop(&bif);//remove o endereço da bifurcação
            tmp = pop(&bif);//passa o endereço do próximo caminho para cam
            push(tmp -> x, tmp -> y, &cam);
            break;

            default:
            printf("erro\n");
            saida = 0;
            break;
        }
    }

    if(conta == 1){
        pop(&cam);
    }

    while(bif != NULL)
        pop(&bif);

    while(cam != NULL){
        tmp = pop(&cam);
        push(tmp -> x, tmp -> y, &bif);
    }

    printpilha(bif);
    printlab(lab);
}