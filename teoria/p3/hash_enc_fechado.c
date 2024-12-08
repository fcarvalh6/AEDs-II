#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*-----------ESTRUTURAS DE DADOS---------------
*/

//para encadeamento fechado
typedef struct estudante2_{
    int matricula;
    char nome[30];
    struct estudante2_* prox;
}estudante2;

//para encadeamento fechado
typedef struct hash2_{
    int qtd, TABLE_SIZE;
    estudante2 ** estudantes;
} hash2;


/*-----------FUNÇÕES DE UTILIDADE--------------
*/

estudante2 * cria_estudante(char * nome, int matricula) {
    estudante2 *e = malloc(sizeof(estudante2));
    e->matricula = matricula;
    strncpy(e->nome, nome, 29);  // Leave space for null terminator
    e->nome[29] = '\0';  // Explicitly null-terminate
    e->prox = NULL;
    return e;
}

hash2 * cria_hash(int TABLE_SIZE) {
	hash2 *ha = malloc(sizeof (hash2));

	if (ha != NULL) {
		int i;
		ha->estudantes = malloc(TABLE_SIZE * sizeof (estudante2 *));
		if (ha->estudantes == NULL) {
			free(ha);
			return NULL;
		}
		ha->TABLE_SIZE = TABLE_SIZE;
		ha->qtd = 0;
		for (i = 0; i < TABLE_SIZE; i++) {
			ha->estudantes[i] = NULL;
		}
	}
	return ha;
}

//esta função deve ser alterada para realizar a liberação correta de memória
void libera_hash(hash2* ha) {
    if (ha == NULL) return;

    //libera cada lista encadeada
    for (int i = 0; i < ha->TABLE_SIZE; i++) {
        estudante2* atual = ha->estudantes[i];
        while (atual != NULL) {
            estudante2* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }

    //libera o vetor de estudantes
    free(ha->estudantes);
    free(ha);
}

/*-----------FUNÇÕES DE HASHING----------------
*/

/*esta função de hashing simples retorna o resto 
da divisão inteira do valor da chave pelo tamanho da tabela
*/ 
int chaveDiv(int chave, int TAM){
    if(chave < 0)
        chave *= -1;//impede que o índice seja negativo
    return (chave%TAM);
}

/*a posição é gerada usando uma constante A, tal que 0 < A < 1,
apenas a parte fracionária é usada para gerar a posição.
*/
int chaveMult(int chave, int TAM){
    if(chave < 0)
        chave *= -1;//impede que o índice seja negativo
    double A = 0.7834729723;
    double val = chave * A;
    val = val - (int)val; //(int)val é a parte inteira, a subtração deixa apenas a parte fracionária
    return (int) (val*TAM);
}

/*a chave é "dobrada" até produzir um valor válido
*/
int chaveDobra(int chave, int TAM){
    if(chave < 0)
        chave *= -1;//impede que o índice seja negativo
    if(chave < TAM)//se a chave for menor que o tamanho, não há necessidade de dobra 
        return chave; 
    
    int numeros[10];//guardará as casas do número passado
    int inicio = 0, fim = 0, div = chave;
    do{//divide o número, colocando cada casa numa posição do vetor
        int resto = div%10;//na primeira iteração, guarda o número das unidades
        numeros[inicio] = resto;//guarda o resto na posição correta
        if(numeros[inicio])//garante que fim aponta para um número
            fim = inicio;
        inicio++;//a próxima casa do vetor será preenchida
        div = div/10;//passa para a próxima casa (potências de 10)
    }while(inicio < 10);
    inicio = 0;//início sempre será a primeira casa do vetor
    
    while(chave > TAM){//as dobras são feitas até chave ser menor que TAM
        while(fim > inicio){//dobra
            numeros[inicio] = (numeros[inicio] + numeros[fim])%10;//soma as extremidades
            numeros[fim] = 0;//remove o número do final
            inicio++;//anda pro centro
            fim--;//anda pro centro
        }

        inicio = 0;
        chave = 0;
        int fator = 1;//fator cresce em potências de 10, corresponde à casa preenchida

        while(inicio <= fim){//constroi a chave com base nos valores no vetor
            chave += numeros[inicio]*fator;//fator 1, unidades, fator 10, dezenas, etc.
            fator *= 10;//fator cresce em potências de 10
            inicio++;
        }
        inicio = 0;
    }
    return chave;
}

/*-----------INSERÇÃO E BUSCA----------------
*/

int insereFechado(hash2* ha, estudante2* e) {
    if (ha == NULL || e == NULL) return 1;

    //outras funções podem ser usadas aqui
    int pos = chaveDiv(e->matricula, ha->TABLE_SIZE);

    // If the list is empty, set as first element
    if (ha->estudantes[pos] == NULL) {
        ha->estudantes[pos] = e;
    } else {
        estudante2* atual = ha->estudantes[pos];
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = e;
    }
    ha->qtd++;
    return 0;
}

// Search in hash table
char* buscaFechado(hash2* ha, int matricula) {
    if (ha == NULL) return NULL;

    int pos = chaveDiv(matricula, ha->TABLE_SIZE);
    estudante2* atual = ha->estudantes[pos];

    while (atual != NULL) {
        if (atual->matricula == matricula) {
            return &(atual->nome[0]);
        }
        atual = atual->prox;
    }

    return NULL;
}

// Remove from hash table
char* removeFechado(hash2* ha, int matricula) {
    if (ha == NULL) return NULL;

    int pos = chaveDiv(matricula, ha->TABLE_SIZE);
    estudante2* atual = ha->estudantes[pos];
    estudante2* anterior = NULL;

    while (atual != NULL) {
        if (atual->matricula == matricula) {
            // If it's the first node
            if (anterior == NULL) {
                ha->estudantes[pos] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            // Store name before freeing
            static char nome[30];
            strcpy(nome, atual->nome);
            
            free(atual);
            ha->qtd--;
            return nome;
        }
        anterior = atual;
        atual = atual->prox;
    }

    return NULL;//valor não encontrado
}

void main(){
    
    //criação da tabela hash
    hash2* ha = cria_hash(100);
    // hash* ha = NULL;
    // hash* ha = cria_hash(1);

    char nome1[] = "Paulo", nome2[] = "Alberto", nome3[] = "Carla";
    int mat1 = 123, mat2 = 223, mat3 = 12;

    estudante2* e1 = cria_estudante(nome1, mat1);
    estudante2* e2 = cria_estudante(nome2, mat2);
    estudante2* e3 = cria_estudante(nome3, mat3);

    //teste de inserção
    printf("Status da inserção 1: %d\n", insereFechado(ha, e1));
    printf("Status da inserção 2: %d\n", insereFechado(ha, e2));
    printf("Status da inserção 3: %d\n", insereFechado(ha, e3));
    
    //teste de busca
    printf("\nResultado da busca 1: %s\n", buscaFechado(ha, mat1));
    printf("Resultado da busca 2: %s\n", buscaFechado(ha, mat2));
    printf("Resultado da busca 3: %s\n", buscaFechado(ha, mat3));

    //teste de remoção
    printf("\nResultado da remoção 1: %s\n", removeFechado(ha, mat1));
    printf("Resultado da remoção 2: %s\n", removeFechado(ha, mat2));
    printf("Resultado da remoção 3: %s\n", removeFechado(ha, mat3));

    //conferindo remoção
    printf("\nBusca por valor removido: %s\n", buscaFechado(ha, mat1));

    libera_hash(ha);
}