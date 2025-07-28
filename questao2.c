#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct No {
    char dado;
    struct No* prox;
} No;

typedef struct {
    No* topo;
} Pilha;

void inicioPilha(Pilha *p) {
    p->topo = NULL;
}

bool vazia(Pilha *p) {
    return p->topo == NULL;
}

void push(Pilha *p, char valor) {
    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro ao alocar memoria!\n");
        exit(1);
    }

    novoNo->dado = valor;
    novoNo->prox = p->topo;
    p->topo = novoNo;
}

char pop(Pilha *p) {
    if (vazia(p)) {
        return '\0';
    }

    No* no_remover = p->topo;
    char valor_desempilhado = no_remover->dado;

    p->topo = p->topo->prox;

    free(no_remover);

    return valor_desempilhado;
}

int main(){
    char txt[260];
    Pilha pilha;
    inicioPilha(&pilha);

    printf("Digite uma palavra ou frase:\n");
    fgets(txt, sizeof(txt), stdin);

    txt[strcspn(txt, "\n")] = '\0';

    for (int i = 0; i < strlen(txt); i++) {
        push(&pilha, txt[i]);
    }

    printf("Saida:\n");

    while(!vazia(&pilha)) {
        printf("%c", pop(&pilha));
    }
    printf("\n");

    return 0;
}