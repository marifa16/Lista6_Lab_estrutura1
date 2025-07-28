#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct No {
    char* dado;
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

void push(Pilha *p, const char* valor) {
    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro em alocar memoria!\n");
        exit(1);
    }
    novoNo->dado = (char*) malloc(strlen(valor) + 1);

    if (novoNo->dado == NULL) {
        printf("Erro em alocar memoria!\n");
        exit(1);
    }
    strcpy(novoNo->dado, valor);

    novoNo->prox = p->topo;
    p->topo = novoNo;
}

char* pop(Pilha *p) {
    if (vazia(p)) {
        return NULL;
    }
    No* no_remover = p->topo;
    char* vslor_desempilhado = no_remover->dado;
    p->topo = p->topo->prox;
    
    free(no_remover);
    return vslor_desempilhado;
}

void liberarPilha(Pilha* p) {
    while (!vazia(p)) {
        char* dado = pop(p);
        free(dado);
    }
}

void exibirAcoes(Pilha* p) {
    printf("\n--- Estado Atual ---\n");
    if (vazia(p)) {
        printf("(Nenhuma ação realizada)\n");
    } else {
        No* atual = p->topo;
        while(atual != NULL) {
            printf("- %s\n", atual->dado);
            atual = atual->prox;
        }
    }
}

int main() {
    Pilha pilha_desfazer, pilha_refazer;
    inicioPilha(&pilha_desfazer);
    inicioPilha(&pilha_refazer);
    
    char entrada[256];

    printf("Sistema de Desfazer/Refazer. Comandos: 'desfazer', 'refazer', 'listar', 'sair'.\n");

    while (true) {
        printf("> ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';

        if (strcmp(entrada, "sair") == 0) {
            break;
        } else if (strcmp(entrada, "desfazer") == 0) {
            if (vazia(&pilha_desfazer)) {
                printf("Nada a desfazer.\n");
            } else {
                char* acao = pop(&pilha_desfazer);

                printf("Acao desfeita: \"%s\"\n", acao);
                push(&pilha_refazer, acao);
                free(acao); 
            }
        } else if (strcmp(entrada, "refazer") == 0) {
            if (vazia(&pilha_refazer)) {
                printf("Nada a refazer.\n");
            } else {
                char* acao = pop(&pilha_refazer);

                printf("Acao refeita: \"%s\"\n", acao);
                push(&pilha_desfazer, acao);
                free(acao);
            }
        } else if (strcmp(entrada, "listar") == 0) {
            exibirAcoes(&pilha_desfazer);
        } else { 
            printf("Acao realizada: \"%s\"\n", entrada);
            push(&pilha_desfazer, entrada);
            
            liberarPilha(&pilha_refazer);
        }
    }

    liberarPilha(&pilha_desfazer);
    liberarPilha(&pilha_refazer);
    printf("Sistema encerrado.\n");

    return 0;
}