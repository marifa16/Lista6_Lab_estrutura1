#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct No {
    char dado;
    struct No* proximo;
} No;

typedef struct {
    No* topo;
} Pilha;

void inicioPilha (Pilha *p) {
    p->topo = NULL;
}

bool vazia(Pilha *p) {
    return p->topo == NULL;
}

void push(Pilha *p, char valor) {
    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro em alocar memoria");
        exit(1); 
    }

    novoNo->dado = valor;
    novoNo->proximo = p->topo;

    p->topo = novoNo;
}

char pop(Pilha *p) {
    if (vazia(p)) {
        return '\0';
    }

    No* no_temp = p->topo;
    char valor_desempilhado = no_temp->dado;

    p->topo = no_temp->proximo;

    free(no_temp);

    return valor_desempilhado;
}

void liberarPilha(Pilha *p) {
    while (!vazia(p)) {
        pop(p);
    }
}

bool verificar(const char *seq) {
    Pilha pilha;
    inicioPilha(&pilha);
    bool resultado = true;

    for (size_t i = 0; i < strlen(seq); i++) {
        char c = seq[i];

        if (c == '(' || c == '{' || c == '[') {
            push(&pilha, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (vazia(&pilha)) {
                resultado = false;
                break;
            }
            char topo = pop(&pilha);

            if ((c == ')' && topo != '(') || (c == '}' && topo != '{') || (c == ']' && topo != '[')) {
                resultado = false;
                break;
            }
        }
    }
    if (resultado && !vazia(&pilha)) {
        resultado = false;
    }
    liberarPilha(&pilha);

    return resultado;
}

int main() {
    const char *entrada1 = "{[()]}";
    const char *entrada2 = "{[([)]}";
    const char *entrada3 = "((())";

    printf("Entrada: %s\n", entrada1);

    if (verificar(entrada1)) {
        printf("Saida: Entrada Balanceada\n");
    } else {
        printf("Saida: Entrada nao Balanceada\n");
    }

    printf("Entrada: %s\n", entrada2);

    if (verificar(entrada2)) {
        printf("Saida: Entrada Balanceada\n");
    } else {
        printf("Saida: Entrada nao Balanceada\n");
    }

    printf("Entrada: %s\n", entrada3);

    if (verificar(entrada3)) {
        printf("Saida: Entrada Balanceada\n");
    } else {
        printf("Saida: Entrada nao Balanceada\n");
    }

    return 0;
}