#include <stdio.h>
#include <stdlib.h>

//cada nó da pilha guarda coordenadas x e y e o endereço do nó abaixo
typedef struct no_ {
    int x;
    int y;
    struct no_* prox;
} no;

/*TODO: 
        - resolver problemas com lab 1
*/

//impressão de labirinto; recebe endereço do labirinto e o imprime.
void printlab(char L[10][10]){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            printf("%c", L[i][j]);
        printf("\n");
    }
}

//impressão de pilha; recebe endereço da pilha e a imprime.
void printpilha(no* t){
    while(t != NULL){
        printf("%d, %d\n", t -> x, t -> y);
        t = t -> prox;
    }
}

//adiciona um nó com as coordenadas passadas à pilha
void push(int xn, int yn, no** t){ 
    no* n = malloc(sizeof(no)); //cria o nó a ser adicionado
    n -> x = xn; //insere o valor de x
    n -> y = yn; //insere o valor de y
    n -> prox = *t; //aponta para o item abaixo
    *t = n;//t aponta para o topo
}

//remove o nó do topo. retornando-o e alterando o ponteiro de topo da lista
no* pop(no** t){
    if(*t != NULL){
        no* tmp = *t;
        *t = (**t).prox;
        return tmp;
    } else return NULL;
}

/*argc e argv são usados para que seja possível passar o nome do labirinto a ser resolvido como argumento
*/
int main(int argc, char* argv[]){

    if(argc != 2){//garante que o número correto de argumentos foi passado
        printf("Número inválido de argumentos\n");
        return -1;// -1 é o erro de número de argumentos
    } else printf("Resolução do labirinto %s\n", argv[1]);

    //LEITURA
    FILE* arq = fopen(argv[1], "r");//o ponteiro arq recebe o endereço do labirinto passado como argumento
    
    if(arq == NULL){//garante que o arquivo passado existe/foi encontrado
        printf("ERRO! Arquivo não foi encontrado!\n");
        return 1;// 1 é o erro de arquivo inválido
    }
    
    char lab[10][10];//o labirinto é guardado numa matriz 10x10

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
            lab[i][j] = fgetc(arq);
        fgetc(arq); //descarta os newlines (\n), que sempre se encontrarão ao final das linhas
    }    
    
    fclose(arq);//fecha o arquivo, encerrando assim a leitura

    //RESOLUÇÃO
    printlab(lab);//imprime o labirinto antes de ser resolvido

    no* cam = NULL;//pilha onde será guardado o caminho percorrido
    no* bif = NULL;//pilha onde serão guardadas as bifurcações

    //ENCONTRA A ENTRADA
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            if(lab[i][j] == 69){
                push(i, j, &cam);
            }

    int saida = 1;//para o código quando a saída é encontrada
    int conta;//conta o número de caminhos seguintes possíveis
    int sonda;//guarda a posição que será analizada
    no* tmp;

    while(saida == 1){//roda enquanto a saída não tiver sido encontrada
        conta = 0;//reinicia o valor toda vez que o loop começa
        int xa = cam -> x;//xa = x atual
        int ya = cam -> y;//ya = y atual

        if(xa > 0){//garante que há casa a ser explorada em cima
            sonda = lab[xa-1][ya];//CIMA

            switch(sonda){
                case 48://48 = ZERO
                push(xa-1, ya, &bif);
                conta++;
                break;
                case 83://83 = S
                push(xa-1, ya, &cam);
                saida = 0;
                conta++;
                break;
            }
        }

        if(ya > 0){//garante que há casa a ser explorada na esquerda
            sonda = lab[xa][ya-1];//ESQUERDA

            switch(sonda){
                case 48://48 = ZERO
                push(xa, ya-1, &bif);
                conta++;
                break;
                case 83://83 = S
                push(xa, ya-1, &cam);
                saida = 0;
                conta++;
                break;
            }
        }

        if(xa < 9){//garante que há casa a ser explorada embaixo
            sonda = lab[xa+1][ya];//BAIXO

            switch(sonda){
                case 48://48 = ZERO
                push(xa+1, ya, &bif);
                conta++;
                break;
                case 83://83 = S
                push(xa+1, ya, &cam);
                saida = 0;
                conta++;
                break;
            }
        }

        if(ya < 9){//garante que há casa a ser explorada na direita
            sonda = lab[xa][ya+1];//DIREITA

            switch(sonda){
                case 48://48 = ZERO
                push(xa, ya+1, &bif);
                conta++;
                break;
                case 83://83 = S
                push(xa, ya+1, &cam);
                saida = 0;
                conta++;
                break;
            }
        }
    
    if(saida == 1){
            switch(conta){

                case 1://há apenas um caminho a ser percorrido
                lab[xa][ya] = 67;//a posição atual recebe C
                tmp = pop(&bif);//pega o primeiro da pilha de bifurcações e guarda na pilha de caminho (próximo a ser acessado)
                push(tmp -> x, tmp -> y, &cam);
                break;

                case 2://há dois caminhos a serem percorridos
                lab[xa][ya] = 67;//a posição atual recebe C
                tmp = pop(&bif);//pega o primeiro da pilha de bifurcações e guarda na pilha de caminho (próximo a ser acessado)
                push(tmp -> x, tmp -> y, &cam);
                push(xa, ya, &bif);//guarda a posição onde ocorreu a bifurcação
                break;

                case 0://não há mais caminhos
                while(cam -> x != bif -> x || cam -> y != bif -> y){//volta até a bifurcação anterior
                    tmp = pop(&cam);
                    free(tmp);//remove o valor do topo de cam
                }
                pop(&bif);//remove o endereço da bifurcação
                tmp = pop(&bif);//passa o endereço do próximo caminho para cam
                push(tmp -> x, tmp -> y, &cam);
                break;

                default://caso de erro
                printf("erro\n");
                saida = 0;
                break;
            }
        }
    }

    while(bif != NULL){//esvazia bif
        tmp = pop(&bif);
        free(tmp);
    }

    while(cam != NULL){//inverte a ordem de cam em bif
        tmp = pop(&cam);
        push(tmp -> x, tmp -> y, &bif);
        free(tmp);
    }

    printpilha(bif);

    return 0;
}