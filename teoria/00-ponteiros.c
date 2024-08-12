#include <stdio.h>
#include <stdlib.h>

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

    return 0;
}