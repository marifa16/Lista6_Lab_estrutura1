#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct No {
    char* nomeCliente; 
    struct No* proximo;
} No;

typedef struct {
    No* frente;
    No* tras;
} Fila;

void inicioFila(Fila *f) {
    f->frente = NULL;
    f->tras = NULL;
}

bool vazia(Fila *f) {
    return f->frente == NULL;
}

void enfileirar(Fila *f, const char* nome) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    
    novoNo->nomeCliente = (char*) malloc(strlen(nome) + 1);
    strcpy(novoNo->nomeCliente, nome);
    novoNo->proximo = NULL;

    if (vazia(f)) {
        f->frente = novoNo;
        f->tras = novoNo;
    } else {
        f->tras->proximo = novoNo;
        f->tras = novoNo;
    }
    printf("Cliente \"%s\" adicionado a fila.\n", nome);
}

char* desenfileirar(Fila *f) {
    if (vazia(f)) {
        return NULL;
    }

    No* no_remover = f->frente;
    char* nome_removido = no_remover->nomeCliente;

    f->frente = f->frente->proximo;

    if (f->frente == NULL) {
        f->tras = NULL;
    }

    free(no_remover);
    return nome_removido;
}

void exibirFila(Fila* f) {
    printf("\n--- Fila de Espera Atual ---\n");
    if (vazia(f)) {
        printf("(Fila vazia)\n");
    } else {
        No* atual = f->frente;
        printf("[");
        while(atual != NULL) {
            printf("'%s'", atual->nomeCliente);
            if(atual->proximo != NULL) {
                printf(", ");
            }
            atual = atual->proximo;
        }
        printf("]\n");
    }
}

void liberarFila(Fila* f) {
    while (!vazia(f)) {
        char* nome = desenfileirar(f);
        free(nome);
    }
}

int main() {
    Fila fila_banco;
    inicioFila(&fila_banco);
    char entrada[256];
    char* comando;
    char* nome;

    printf("Simulador de Fila de Banco.\n");
    printf("Comandos: adicionar <nome>, atender, exibir, sair\n");

    while (true) {
        printf("> ");
        fgets(entrada, sizeof(entrada), stdin);
        
        entrada[strcspn(entrada, "\n")] = '\0';
        
        comando = strtok(entrada, " ");

        if (comando == NULL) continue; // Linha vazia

        if (strcmp(comando, "adicionar") == 0) {
            nome = strtok(NULL, ""); 
            if (nome != NULL) {
                enfileirar(&fila_banco, nome);
            } else {
                printf("Comando invalido. Use: adicionar <nome>\n");
            }
        } 
        else if (strcmp(comando, "atender") == 0) {
            if (vazia(&fila_banco)) {
                printf("Nenhum cliente para atender.\n");
            } else {
                char* cliente_atendido = desenfileirar(&fila_banco);
                printf("Atendendo %s\n", cliente_atendido);
                free(cliente_atendido); 
            }
        } else if (strcmp(comando, "exibir") == 0) {
            exibirFila(&fila_banco);
        } else if (strcmp(comando, "sair") == 0) {
            break;
        } else {
            printf("Comando desconhecido.\n");
        }
    }

    liberarFila(&fila_banco);
    printf("Sistema encerrado.\n");
    return 0;
}