#include <stdio.h>
#include <stdlib.h>

void dobra_val(int n);

void dobra_ref(int *n);

void preenche(int *p, int tam);

void imprime(int *p, int tam);

typedef struct pf{
    char nome[50];
    char sexo;
    int idade;
}pessoaFisica;

void imprimeStruct(pessoaFisica p);

void defineSexo(char* sexo);

void defineNome(char* nome);

void preencheStruct(pessoaFisica* p);

int main() {
// -- PONTEIROS EM LINGUAGEM C --

//PARTE 1: INTRODUÇÃO
    printf("PARTE 1\n");

/*  Endereços podem ser interpretados por meio de uma analogia: são como endereços de casas. As casas e
seus ocupantes podem mudar, mas seu endereço nunca muda. Os endereços, na memória, são utilizados para se referir
a uma das regiões de memória, que têm valores numéricos definidos que nunca se repetem. 
*/
    int num1 = 0; //nesta declaração, uma região de memória foi definida como num1 e 0 foi atribuído ao seu valor
    num1 = 1; //nesta declaração, o valor de num1 muda, mas seu endereço permanece o mesmo: ainda é aquele espaço de memória atribuído na linha anterior

    printf("%d\n", num1); //imprime o CONTEÚDO guardado em num1
    printf("%p\n", &num1); //imprime o ENDEREÇO de num1 (em hexadecimal)

    num1 = 2;

    printf("%d\n", num1); //imprime o CONTEÚDO guardado em num1, que agora é 2
    printf("%p\n", &num1); //imprime o ENDEREÇO de num1, note que ele não mudou
    
/*  Agora que endereços foram esclarecidos, pode-se discutir a utilidade de ponteiros. Ponteiros são variáveis
que não guardam valores, mas sim endereços de outras variáveis (desta forma, pode-se dizer que "apontam" para variáveis) 
*/

    int *pont1 = &num1; //pont1 está armazenando o endereço de num1 ("apontando" para ela)

    printf("%d\n", num1); //imprime o CONTEÚDO de num1
    printf("%p\n", &num1); //imprime o ENDEREÇO de num1
    printf("%p\n", pont1); //imprime o CONTEÚDO de pont1, que é o ENDEREÇO de num1
    printf("%p\n", &pont1); //imprime o ENDEREÇO de pont1

//PARTE 2: PONTEIRO DE PONTEIRO
    printf("PARTE 2\n");

    num1 = 0; //variáveis comuns guardam valores
    pont1 = &num1; //variáveis ponteiro guardam endereços de variáveis comuns
    int **pont2 = &pont1; //variáveis ponteiro de ponteiro guardam endereços de variáveis ponteiro
    int ***pont3 = &pont2; //não há limite! (**********pont10 = &pont9)

    printf("%p\n", pont2); //conteúdo de pont 2 = endereço de pont1
    printf("%p\n", &pont1);

    printf("%p\n", *pont2); //* = para onde esta variável aponta, neste caso pont1, que é igual ao endereço de num1
    printf("%p\n", &num1);

    printf("%d\n", **pont2); //** = vai para onde está apontando, depois vá para onde ele está apontando, neste caso, num1!
    printf("%d\n", num1);

//PARTE 3: PASSAGEM DE PARÂMETRO POR VALOR E REFERÊNCIA
    printf("PARTE 3\n");

    num1 = 2; //iniciado como 2
    dobra_val(num1); //valor é dobrado e impresso
    printf("%d\n", num1); //porém, o valor da variável num1 NÃO MUDA
    printf("%p\n", &num1);

/*  Isto acontece porque no exemplo anterior foi feita uma chamada por VALOR, apenas o valor de num1 foi passado,
não a variável em si. O valor dobrado foi o da variável local n, não o de num1. Note que &num1 != &n, porque são
variáveis diferentes e independentes.
    Também existe a passagem por referência, que será vista abaixo.
*/

    dobra_ref(&num1); //valor é dobrado e impresso
    printf("%d\n", num1); //desta vez, o valor muda
    printf("%p\n", &num1); //note que os endereços são iguais

//PARTE 4: Alocação dinâmica de memória & Aritmética de ponteiros
    printf("PARTE 4\n");

    int *pont = malloc(sizeof(int)); //aloca uma região de memória com o tamanho especificado e guarda o endereço na variável

    *pont = 100; //atribui 100 ao lugar apontado pela variável

    printf("%d\n", *pont);

    free(pont); //libera a região da memória antes reservada. REGRA: "para cada malloc, você vai precisar de um free"

/*Mas e seu eu precisar de espaço para mais elementos?
*/
    int num_elementos = 4;
    pont = malloc(num_elementos * sizeof(int)); //agora foram reservadas 4 regiões de memória para números inteiros

    for(int i = 0; i < num_elementos; i++){
        printf("%p\n", (pont + i)); //pont + i = endereço contido em pont + i * sizeof(int)
        *(pont + i) = i + i;
    }

    for(int i = 0; i < num_elementos; i++){
        printf("%d\n", *(pont + i)); //imprime o valor apontado por pont + i
    }

/*Existe também uma outra notação:
*/

    for(int i = 0; i < num_elementos; i++){
        pont[i] = i + i; //Cuidado! Não resulta no mesmo tipo de alocação que a de um vetor
    }

    for(int i = 0; i < num_elementos; i++){
        printf("%d\n", pont[i]);
    }

/*Agora utilizando uma função: 
*/

    preenche(pont, num_elementos);

    imprime(pont, num_elementos);

    free(pont);

    double *pontd = malloc(num_elementos * sizeof(double)); //espaço para 4 doubles reservado

    for(int i = 0; i < num_elementos; i++){
        printf("%p\n", (pontd + i)); //pont + i = endereço contido em pontd + i * sizeof(double)

    }

    free(pontd);

//PARTE 5: Ponteiros e dimensões
    printf("PARTE 5\n");

/*  Anteriormente, vimos como a alocação dinâmica usando malloc pode ser usada para ter funcionalidade bastante
parecida com a de um vetor, agora veremos como figuras com mais dimensões podem ser criadas.
    A estrutura "padrão" de uma matriz faz uso de um ponteiro de ponteiro que aponta para um vetor de ponteiros,
cada ponteiro deste vetor corresponde a uma linha da matriz e aponta por sua vez para um vetor de valores.
*/
    int num_linhas = 2;
    int num_colunas = 4;

    int matriz[num_linhas][num_colunas]; //cria uma matriz com duas linhas e quatro colunas

    int **pontlinhas = malloc(num_linhas * sizeof(int)); //forma um vetor de ponteiros correspondente às linhas

    for(int i = 0; i < num_linhas; i++){
        *(pontlinhas + i) = malloc(num_colunas * sizeof(int)); //forma um vetor de valores correspondente às colunas
        for(int j = 0; j < num_colunas; j++){
            *(*(pontlinhas + i) + j) = i + j; //pont[i][j] = i + j é uma notação válida
        }
    }

    for(int i = 0; i < num_linhas; i++){
        for(int j = 0; j < num_colunas; j++)
            printf("%4d", *(*(pontlinhas + i) + j));
        printf("\n");
    }
    printf("\n");
/*  Agora como a memória é liberada?
*/

    for(int i = 0; i < num_linhas; i++){
        free(*(pontlinhas + i));
    }

//    free(pontlinhas);

/*  Primeira dimensão: ponteiro; Segunda dimensão: ponteiro de ponteiro; Terceira dimensão: ponteiro de ponteiro de ponteiro! 
*/

//EXTRA: struct em funções
    printf("EXTRA\n");

/*  ver o typedef no início do código e as funções imprimeStruct, defineSexo e defineNome
*/
    pessoaFisica pf;

    pf.sexo = 'f';
    pf.idade = 18;

/* vetores ou matrizes sempre são passados por referência, mas vetores dentro de structs não seguem essa regra
se a struct é passada como valor
*/

    defineSexo(&pf.sexo);

    defineNome(&pf.nome[0]);

    preencheStruct(&pf);

    imprimeStruct(pf);

    return 0;
}

void dobra_val(int n){
    n = n*2;
    printf("%d\n", n);
    printf("%p\n", &n);
}

void dobra_ref(int *n){
    *n = (*n)*2; //onde n aponta = num1
    printf("%d\n", *n);
    printf("%p\n", n);
}

void preenche(int *p, int tam){
    for(int i = 0; i < tam; i++){
        *(p + i) = i + i;
    }
}

void imprime(int *p, int tam){
    for(int i = 0; i < tam; i++){
        printf("%d\n", *(p + i));
    }
}

void imprimeStruct(pessoaFisica p){
    printf("Nome: %s\n", p.nome);
    printf("Sexo: %c\n", p.sexo);
    printf("Idade: %i\n", p.idade);
}

void defineSexo(char* sexo){
    printf("Informe o sexo: ");
    scanf("%c", sexo);
}

void defineNome(char* nome){
    printf("Informe o nome: ");
    scanf("%s", nome);
}

void preencheStruct(pessoaFisica* p){
    printf("Informe o nome: ");
    scanf("%s", &((*p).nome[0])); //*p.nome causa erro de compilação, (*p).nome funciona
    getchar();
    printf("Informe o sexo: ");
    scanf("%c", &p->sexo);
    printf("Informe a idade: ");
    scanf("%d", &((*p).idade));
}