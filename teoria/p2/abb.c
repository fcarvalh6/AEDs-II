#include <stdio.h>
#include <stdlib.h>

/*-----> ESTRUTURA DE DADOS: NÓ <-----*/

typedef struct no_ {
    int valor; //valor guardado no nó
    struct no_* esquerda; //ponteiro para o nó da esquerda
    struct no_* direita; //ponteiro para o nó da direita
} no;

/*-----> ALGORITMOS DE CAMINHAMENTO <-----*/

//percorre a árvore utilizando o método em-ordem
void em_ordem(no* n) {
    if (n == NULL) //se n == NULL, este é o fim da árvore/subárvore, portanto retorne
        return; 

    em_ordem(n -> esquerda); //percorre a subárvore esquerda

    printf("%d ", n -> valor); //visita o nó

    em_ordem(n -> direita); //percorre a subárvore direita
}

//percorre a árvore utilizando o método pré-ordem
void pre_ordem(no* n) {
    if (n == NULL) //se n == NULL, este é o fim da árvore/subárvore, portanto retorne
        return; 

    printf("%d ", n -> valor); //visita o nó

    pre_ordem(n -> esquerda); //percorre a subárvore esquerda

    pre_ordem(n -> direita); //percorre a subárvore direita
}

//percorre a árvore utilizando o método pré-ordem
void pos_ordem(no* n) {
    if (n == NULL) //se n == NULL, este é o fim da árvore/subárvore, portanto retorne
        return; 

    pos_ordem(n -> esquerda); //percorre a subárvore esquerda

    pos_ordem(n -> direita); //percorre a subárvore direita

    printf("%d ", n -> valor); //visita o nó
}

/*-----> CRIAÇÃO E INSERÇÃO DE NÓS <-----*/

//cria um nó com o valor passado, retorna seu endereço
no* cria_no(int k){
    no* tmp = malloc(sizeof(no)); //reserva um endereço para armazenar os dados
    tmp -> valor = k; //o valor do nó criado é o inteiro passado para a função
    tmp -> esquerda = tmp -> direita = NULL; //ambos os ponteiros apontam para NULL
    return tmp; //retorna o endereço do nó criado
}

//insere o nó na árvore, retornando a raiz
no* insere(no* raiz, no* n){
    if(raiz == NULL) //se a raiz for nula, este é o local para a inserção, portanto retorne n 
        return n; //note que n será retornado para o nível acima, sendo apontado por ele
    
    if(raiz -> valor > n -> valor) //se o valor do nó analisado for maior que n
        raiz -> esquerda = insere(raiz -> esquerda, n); //percorra a subárvore esquerda
    else    
        raiz -> direita = insere(raiz -> direita, n); //percorra a subárvore direita
    
    return raiz; //ao final, retorne raiz (o endereço do nó analisado)
}

/*-----> BUSCA <-----*/

//busca pelo nó com o valor passado, retornando seu endereço
no* busca(no* raiz, int k){
    if(raiz == NULL || (raiz -> valor) == k) //se raiz for NULL, este é o fim da subárvore
        return raiz; //se raiz -> valor for igual a k, o nó foi encontrado

    if(raiz -> valor > k) //se o valor do nó analisado for maior que k
        return busca(raiz -> esquerda, k); //percorra a subárvore esquerda
    else 
        return busca(raiz -> direita, k); //percorra a subárvore direita
}

/*-----> REMOÇÃO <-----*/

//retorna o endereço do nó de valor máximo na subárvore passada
no* max(no* n){
    while(n->direita != NULL) //enquanto houverem nós à direita
        n = n->direita; //anda para a direita
    return n; //retorna o endereço do maior valor da subárvore com raiz n (o n inicial)
}

//retorna o endereço do pai do nó n
no* busca_pai(no* raiz, no* n){
    //caso onde se chega ao final da árvore sem encontrar o valor ou quando n é raiz
    if(raiz == NULL || raiz == n)
        return NULL; //retorna NULL porque n ainda não foi encontrado ou n não tem pai

    //se n for filho do nó analisado
    if(raiz -> esquerda == n || raiz -> direita == n)
        return raiz; //retorna o nó analisado, ele é o pai de n

    //se o valor de n for maior que o do nó analisado
    if(n -> valor > raiz -> valor)
        return busca_pai(raiz -> direita, n); //percorre a subárvore direita

    else return busca_pai(raiz -> esquerda, n); //percorre a subárvore esquerda
}

//remove a raiz passada e retorna a nova raiz
no* remove_raiz(no* raiz){
    //caso sem filhos
    if(raiz->esquerda == NULL && raiz -> direita == NULL){ //se ambos os ponteiros de filho forem nulos
        free(raiz); //libera o endereço da raiz
        return NULL;
    }

    //casos de um único filho
    if(raiz->esquerda == NULL){ //se não tem filho à esquerda
        no* tmp = raiz->direita; //tem filho à direita e ele será usado pra substituir o pai removido
        free(raiz);
        return tmp; //filho à direita
    }

    if(raiz->direita == NULL){ //se não tem filho à direita
        no* tmp = raiz->esquerda; //tem filho à esquerda e ele será usado pra substituir o pai removido
        free(raiz);
        return tmp; //filho à esquerda
    }

    //caso de dois filhos, o nó que substiruirá a raiz é o seu antecessor em ordem crescente
    no* antecessor = max(raiz->esquerda); //nó antecessor
    no* pai = busca_pai(raiz, antecessor); //encontra o pai do antecessor

    raiz->valor = antecessor->valor; //o valor do antecessor "salta" para a raiz que será removida

    //reorganiza os endereços em torno do nó apagado
    if(pai == raiz) //se a raiz for o pai, antecessor é filho da raiz
        raiz->esquerda = antecessor->esquerda; //filho esquerdo de antecessor passa a ser apontado pelo pai 
    else //se a raiz não for o pai, a substituição ocorrerá involvendo o pai encontrado
        pai->direita = antecessor->esquerda; //filho esquerdo de antecessor passa a ser apontado pelo pai
    
    free(antecessor); //antecessor é removido após seu valor passar para a raiz
    return raiz;
}

no* remove_no(no* raiz, int k){
    no* n = busca(raiz, k); //guarda o endereço do nó, NULL caso ele não exista 

    if(n){//se o nó existe (NULL == falso, qualquer endereço diferente de NULL é verdadeiro)
        no* pai = busca_pai(raiz, n); //guarda a posição do pai
        if(pai){//se ele não tem pai, ele é a raiz

            if((pai -> direita) == n)//se ele for o filho à direita, então o ponteiro "direita" do pai é atualizado
                pai -> direita = remove_raiz(n);//a atualização é feita pela função remove_raiz
            else
                pai -> esquerda = remove_raiz(n);//se ele for o filho à esquerda, então o ponteiro "esquerda" do pai é atualizado
        } else raiz = remove_raiz(n); //se ele não tem pai, ele é a raiz, então remova n
    }
    return raiz; //retorna a raiz atualizada da árvore
}

int main(){
    //valores para a criação de nós
    int v1 = 2;
    int v2 = 1;
    int v3 = 3;
    int v4 = 5;
    int v5 = 4;
    int v6 = 6;

    //cria nós para os testes
    no* n1 = cria_no(v1);
    no* n2 = cria_no(v2);
    no* n3 = cria_no(v3);
    no* n4 = cria_no(v4);
    no* n5 = cria_no(v5);
    no* n6 = cria_no(v6);

    //a raiz é iniciada como NULL (árvore vazia)
    no* raiz = NULL;

    //teste de inserções 
    raiz = insere(raiz, n1); //no caso de árvore vazia, raiz passa de NULL para n1
    raiz = insere(raiz, n2);
    raiz = insere(raiz, n3);
    raiz = insere(raiz, n4);
    raiz = insere(raiz, n5);
    raiz = insere(raiz, n6);

    //teste de caminhamento
    printf("\nEm-Ordem: ");
    em_ordem(raiz);
    printf("\nPré-Ordem: ");
    pre_ordem(raiz);
    printf("\nPós-Ordem: ");
    pos_ordem(raiz);
    printf("\n\n");

    //teste de busca
    printf("endereço de n1: %p\n", n1);
    printf("endereço encontrado ao buscar pelo valor de n1: %p\n\n", busca(raiz, v1));

    printf("endereço de n4: %p\n", n4);
    printf("endereço encontrado ao buscar pelo valor de n4: %p\n\n", busca(raiz, v4));

    printf("endereço de n6: %p\n", n6);
    printf("endereço encontrado ao buscar pelo valor de n6: %p\n\n", busca(raiz, v6));

    //teste de remoções
    raiz = remove_no(raiz, v1); //remove o valor 2
    em_ordem(raiz);
    printf("\n");

    raiz = remove_no(raiz, v2); //remove o valor 1
    em_ordem(raiz);
    printf("\n");

    raiz = remove_no(raiz, v5); //remove o valor 4
    em_ordem(raiz);
    printf("\n");

    raiz = remove_no(raiz, v6); //remove o valor 6
    em_ordem(raiz);
    printf("\n");

    raiz = remove_no(raiz, v3); //remove o valor 3
    em_ordem(raiz);
    printf("\n");

    raiz = remove_no(raiz, v4); //remove o valor 5
    em_ordem(raiz);
    printf("\n");

    return 0;
}