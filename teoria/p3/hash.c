#include<stdio.h>
#include<stdlib.h>

/**
 * TODO!
 * implementar as funções do encadeamento separado:
 *  - insere_hash_enc_separado
 *  - busca_hash_enc_separado
 *  - remove_hash_enc_separado
 *  - remove aberto
 */

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
	estudante *e = malloc(sizeof (estudante));
	e->matricula = matricula;
	strncpy(e->nome, nome, strlen(nome));
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

/*produz um índice com base em uma string
*/
int valorString(char* str, int TAM){
    int valor = 7;
    int tam = strlen(str);
    for(int i = 0; i < tam; i++)
        valor = 31*valor + (int)str[i];
    return valor%TAM;
}

/*o hashing universal minimiza colisões, reduzindo a probabilidade matematicamente,
esta função provavelmente não vai cair na prova, já que não estava no código fonte.
*/
int chaveUniv(int chave, int TAM){
    //implementação não foi incluida
}

/*-----------TRATAMENTO DE COLISÃO----------------
*/

//sondagem linear
int sondagem_linear(int pos, int i, int TABLE_SIZE) {
	return ((pos + i) % TABLE_SIZE);
}

//sondagem quadrática
int sondagem_quadratica(int pos, int i, int TABLE_SIZE) {
	pos = pos + 2 * i + 5 * i*i;
	return (pos % TABLE_SIZE);
}

//duplo hash, onde H1 é o resultado da primeira função de hashing
int duploHash(int H1, int chave, int i, int TAM){
    //garantindo que a função chaveDiv não retorne 0
    int H2 = chaveDiv(chave, TAM-1)+1;
    return ((H1 + i * H2)%TAM);
}

/*-----------INSERÇÃO E BUSCA----------------
*/

//SEM COLISÃO

int insere_hash_s_colisao(hash * ha, estudante * e) {
	if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
		return 0;
	}
	int pos = chave_divisao(e->matricula, ha->TABLE_SIZE);

	ha->estudantes[pos] = e;
	ha->qtd++;
	return 1;
}

char* busca_hash_s_colisao(hash * ha, int matricula) {
	int pos = chave_divisao(matricula, ha->TABLE_SIZE);
	return &(ha->estudantes[pos]->nome[0]);
}

//ENDEREÇAMENTO ABERTO

int insereAberto(hash * ha, estudante * e) {
	if (ha == NULL || ha->qtd == ha->TABLE_SIZE) {
		return 0;
	}
	int pos, i;
	pos = chave_dobra(e->matricula, ha->TABLE_SIZE);
    /*OU
    	pos = chave_divisao(e->matricula, ha->TABLE_SIZE);
      OU
	    pos = chave_multiplicacao(e->matricula, ha->TABLE_SIZE);
    */

	for (i = 0; i < ha->TABLE_SIZE; i++) {
		pos = duplo_hash(pos, e->matricula, i, ha->TABLE_SIZE);
        /*OU
            pos = sondagem_linear(pos, i, ha->TABLE_SIZE);
          OU
		    pos = sondagem_quadratica(pos, i, ha->TABLE_SIZE);
        */

		if (ha->estudantes[pos] == NULL) {
			ha->estudantes[pos] = e;
			ha->qtd++;
			return 1;
		}
	}
	return 0;
}

char* buscaAberto(hash * ha, int matricula) {
	int i, pos;
	pos = chaveDobra(matricula, ha->TABLE_SIZE);
	/*OU
		pos = chave_divisao(matricula, ha->TABLE_SIZE);
	  OU
		pos = chave_multiplicacao(e->matricula, ha->TABLE_SIZE);
	*/

	for (i = 0; i < ha->TABLE_SIZE; i++) {
		pos = duploHash(pos, matricula, i, ha->TABLE_SIZE);
		/*OU
			pos = sondaLin(pos, i, ha->TABLE_SIZE);
		  OU
			pos = sondaQuad(pos, i, ha->TABLE_SIZE);
		*/

		if (ha->estudantes[pos] == NULL) {
			return NULL;
		} else if (ha->estudantes[pos]->matricula == matricula) {
			return &(ha->estudantes[pos]->nome[0]);
		}
	}
	return NULL;
}

char* removeAberto(){

}

//ENDEREÇAMENTO FECHADO

int insereFechado(){

}

char* buscaFechado(){

}

char* removeFechado(){

}

void main(){
    const int TAM = 20;
}