#ifndef _H_PILHA
#define _H_PILHA

typedef struct no_ {
    int valor;
    struct no_* p;
} no;

bool ehVazia(no** t);
void push(int v, no** t);
int pop(no** t);
int obtem_elemento(no** t);

#endif // _H_PILHA