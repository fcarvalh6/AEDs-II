#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*-----------ESTRUTURAS DE DADOS---------------
*/

//estrutura para o vetor de estudantes
typedef struct estudante_{
	int matricula;//chave
	char nome[30];//valor
}estudante;

//estrutura para a tabela hash em si, as inserções são feitas no vetor de estudantes
typedef struct hash_{
	int qtd, TABLE_SIZE;//qtd = quantidade de elementos inseridos,
	//TABLE_SIZE = tamanho da tabela.
	estudante ** estudantes;//vetor de estudantes.
}hash;

/*-----------FUNÇÕES DE UTILIDADE--------------
*/

estudante * cria_estudante(char * nome, int matricula) {
    estudante *e = malloc(sizeof(estudante));
    e->matricula = matricula;
    strncpy(e->nome, nome, 29);  // Leave space for null terminator
    e->nome[29] = '\0';  // Explicitly null-terminate
    return e;
}

hash * cria_hash(int TABLE_SIZE) {
	hash *ha = malloc(sizeof (hash));

	if (ha != NULL) {
		int i;
		ha->estudantes = malloc(TABLE_SIZE * sizeof (estudante *));
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

void libera_hash(hash * ha) {
	if (ha != NULL) {
		int i;

		for (i = 0; i < ha->TABLE_SIZE; i++) {
			if (ha->estudantes[i] != NULL)
				free(ha->estudantes[i]);
		}
		free(ha->estudantes);
		free(ha);
	}
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

/*-----------INSERÇÃO E BUSCA----------------
*/

//SEM COLISÃO

int insereSimples(hash * ha, estudante * e) {
	if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {//caso de tabela inexistente ou tabela cheia 
		return 0;
	}
    //outras funções podem ser usadas para encontrar a posição adequada
	int pos = chaveDiv(e->matricula, ha->TABLE_SIZE);

	ha->estudantes[pos] = e;//valor é inserido
	ha->qtd++;
	return 1;
}

//retorna o endereço do valor procurado
char* buscaSimples(hash * ha, int matricula) {
    //outras funções podem ser usadas para encontrar a posição adequada
	int pos = chaveDiv(matricula, ha->TABLE_SIZE);
	return &(ha->estudantes[pos]->nome[0]);
}

char* removeSimples(hash* ha, int matricula){
    int pos = chaveDiv(matricula, ha->TABLE_SIZE);
    char* tmp = &(ha->estudantes[pos]->nome[0]);//endereço do nó procurado
    ha->estudantes[pos] = NULL;//remove o valor
	return tmp;
}

void main(){

    //criação da tabela hash
    hash* ha = cria_hash(100);
    // hash* ha = NULL;
    // hash* ha = cria_hash(1);

    char nome1[] = "Paulo", nome2[] = "Alberto", nome3[] = "Carla";
    int mat1 = 123, mat2 = 223, mat3 = 12;

    estudante* e1 = cria_estudante(nome1, mat1);
    estudante* e2 = cria_estudante(nome2, mat2);
    estudante* e3 = cria_estudante(nome3, mat3);

    //teste de inserção
    printf("Status da inserção 1: %d\n", insereSimples(ha, e1));
    printf("Status da inserção 2: %d\n", insereSimples(ha, e2));
    printf("Status da inserção 3: %d\n", insereSimples(ha, e3));
    
    //teste de busca
    printf("\nResultado da busca 1: %s\n", buscaSimples(ha, mat1));
    printf("Resultado da busca 2: %s\n", buscaSimples(ha, mat2));
    printf("Resultado da busca 3: %s\n", buscaSimples(ha, mat3));

    //teste de remoção
    printf("\nResultado da remoção 1: %s\n", removeSimples(ha, mat1));
    // printf("\nResultado da remoção 2: %s", removeSimples(ha, mat2));//causa segfault porque o valor foi removido
    printf("Resultado da remoção 3: %s\n", removeSimples(ha, mat3));

    libera_hash(ha);
}