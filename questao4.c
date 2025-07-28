#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct No {
    int dado;
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

void push(Pilha *p, int valor) {
    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro em alocaçao de memoria!\n");
        exit(1);
    }
    novoNo->dado = valor;
    novoNo->prox = p->topo;
    p->topo = novoNo;
}

int pop(Pilha *p) {
    if (vazia(p)) {
        printf("Erro.\n");
        return 0;
    }

    No* no_remover = p->topo;

    int valor_desempilhado = no_remover->dado;
    p->topo = p->topo->prox;

    free(no_remover);

    return valor_desempilhado;
}

int avaliar(const char* posfixa) {
    Pilha pilha;
    inicioPilha(&pilha);

    char posfixa_c[512];
    strcpy(posfixa_c, posfixa);

    char* token = strtok(posfixa_c, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(&pilha, atoi(token));
        } else {
            int op2 = pop(&pilha);
            int op1 = pop(&pilha);

            int r = 0;

            switch (token[0]) {
                case '+': r = op1 + op2; break;
                case '-': r = op1 - op2; break;
                case '*': r = op1 * op2; break;
                case '/': 
                if (op2 == 0) {
                    printf("Erro, pois eh uma divisao por 0!\n");
                    exit(1);
                }
                r = op1 / op2;
                break;
            }
            push(&pilha, r);
        }
        token = strtok(NULL, " ");
    }
    return pop(&pilha);
}

int main() {
    const char *entrada1 = "3 4 + 2 *";
    int r1 = avaliar(entrada1);

    printf("Entrada: %s\n", entrada1);
    printf("Saida: %d\n\n", r1);

    const char *entrada2 = "5 2 3 + * 8 4 / -";
    int r2 = avaliar(entrada2);

    printf("Entrada: %s\n", entrada2);
    printf("Saida: %d\n", r2);

    return 0;
}