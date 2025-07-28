#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct No {
    char dado;
    struct No* prox;
} No;

typedef struct {
    No* topo;
} Pilha;

void inicioPilha(Pilha *p) {
    p->topo == NULL;
}

bol vazia(Pilha *p) {
    return p->topo == NULL;
}

void push(Pilha *p, char valor) {
    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro em alocar memoria!\n");
        exit(1);
    }
    novoNo->dado = valor;
    novoNo->prox = p->topo;
    p->topo = novoNo;
}

char pop(Pilha *p) {
    if (vazia(p)) return '\0';

    No* no_remover = p->topo;

    char valor_desempilhado = no_remover->dado;
    p->topo = p->topo->prox;

    free(no_remover);

    return valor_desempilhado;
}

int precedencia(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void infixa_para_posfixa(const char* infixa, char* posfixa) {
    Pilha pilha;
    inicioPilha(&pilha);
    int j = 0;

    char infixa_c[512];
    strcpy(infixa_c, infixa);

    char* token = strtok(infixa_c, " ");

    while (token != NULL) {
        if (isdigit(token[0])) {
            j += sprintf(posfixa + j, "%s ", token);
        } else if (token[0] == '(') {
            push(&pilha, token[0]);
        } else if (token[0] == ')') {
            while (!vazia(&pilha) && pilha.topo->dado != '(') {
                j += sprintf(posfixa + j, "%c ", pop(&pilha));
            }
            pop(&pilha);
        } else {
            while (!vazia(&pilha) && precedencia(pilha.topo->dado) >= precedencia(token[0])) {
                j += sprintf(posfixa + j, "%c ", pop(&pilha));
            }
            push(&pilha, token[0]);
        }
        token = strtok(NULL, " ");
    }

    while (!vazia(&pilha)) {
        j += sprintf(posfixa + j, "%c ", pop(&pilha));
    }

    if (j > 0) {
        posfixa[j - 1] = '\0';
    }
}

int main() {
    const char *entrada1 = "( 3 + 4 ) * 2";
    char saida1[512] = "";

    infixa_para_posfixa(entrada1, saida1);

    printf("Entrada: %s\n", entrada1);
    printf("Saida: %s\n", saida1);

    const char *entrada2 = "5 * ( 2 + 3 ) - 8 / 4";
    char saida2[512] = "";

    infixa_para_posfixa(entrada2, saida2);

    printf("Entrada: %s\n", entrada2);
    printf("Saida: %s\n", saida2);

    return 0;
}