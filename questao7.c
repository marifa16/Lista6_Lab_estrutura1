#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct No {
    char* nomeDocumento; 
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
    
    novoNo->nomeDocumento = (char*) malloc(strlen(nome) + 1);
    strcpy(novoNo->nomeDocumento, nome);
    novoNo->proximo = NULL;

    if (vazia(f)) {
        f->frente = novoNo;
        f->tras = novoNo;
    } else {
        f->tras->proximo = novoNo;
        f->tras = novoNo;
    }
    printf("Documento \"%s\" adicionado a fila de impressao.\n", nome);
}

char* desenfileirar(Fila *f) {
    if (vazia(f)) {
        return NULL;
    }

    No* no_remover = f->frente;
    char* nome_removido = no_remover->nomeDocumento;

    f->frente = f->frente->proximo;

    if (f->frente == NULL) {
        f->tras = NULL;
    }

    free(no_remover);
    return nome_removido;
}

void exibirFila(Fila* f) {
    printf("\n--- Fila de Impressao Atual ---\n");
    if (vazia(f)) {
        printf("(Nenhum documento na fila)\n");
    } else {
        No* atual = f->frente;
        printf("[");
        while(atual != NULL) {
            printf("'%s'", atual->nomeDocumento);
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
    Fila fila_impressao;
    inicioFila(&fila_impressao);
    char entrada[256];
    char* comando;
    char* nome_arquivo;

    printf("Simulador de Fila de Impressao.\n");
    printf("Comandos: adicionar <documento>, imprimir, exibir, sair\n");

    while (true) {
        printf("> ");
        fgets(entrada, sizeof(entrada), stdin);
        
        entrada[strcspn(entrada, "\n")] = '\0';
        
        comando = strtok(entrada, " ");

        if (comando == NULL) continue;

        if (strcmp(comando, "adicionar") == 0) {
            nome_arquivo = strtok(NULL, ""); 
            if (nome_arquivo != NULL) {
                enfileirar(&fila_impressao, nome_arquivo);
            } else {
                printf("Comando invalido. Use: adicionar <nome do documento>\n");
            }
        } 
        else if (strcmp(comando, "imprimir") == 0) {
            if (vazia(&fila_impressao)) {
                printf("Nenhum documento para imprimir.\n");
            } else {
                char* documento_impresso = desenfileirar(&fila_impressao);
                printf("Imprimindo %s\n", documento_impresso);
                free(documento_impresso); 
            }
        }
        else if (strcmp(comando, "exibir") == 0) {
            exibirFila(&fila_impressao);
        }
        else if (strcmp(comando, "sair") == 0) {
            break;
        }
        else {
            printf("Comando desconhecido.\n");
        }
    }

    liberarFila(&fila_impressao);
    printf("Sistema encerrado.\n");
    return 0;
}