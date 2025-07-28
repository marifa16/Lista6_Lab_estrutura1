#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char nome[50];
    int tempo_restante;
} Processo;

typedef struct No {
    Processo processo;
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

void enfileirar(Fila *f, Processo p) {
    No* novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    novoNo->processo = p; 
    novoNo->proximo = NULL;

    if (vazia(f)) {
        f->frente = novoNo;
        f->tras = novoNo;
    } else {
        f->tras->proximo = novoNo;
        f->tras = novoNo;
    }
}

Processo desenfileirar(Fila *f) {
    if (vazia(f)) {
        Processo p_vazio = {"", 0};
        printf("Erro: Fila vazia!\n");
        return p_vazio;
    }

    No* no_remover = f->frente;
    Processo processo_removido = no_remover->processo;

    f->frente = f->frente->proximo;

    if (f->frente == NULL) {
        f->tras = NULL;
    }

    free(no_remover);
    return processo_removido;
}

void simularRoundRobin(Fila* fila, int quantum) {
    printf("--- Iniciando Escalonamento Round-Robin (Quantum: %ds) ---\n", quantum);

    while (!vazia(fila)) {
        Processo p_atual = desenfileirar(fila);

        int tempo_de_execucao = (p_atual.tempo_restante < quantum) ? p_atual.tempo_restante : quantum;

        printf("Executando %s por %ds (restam %ds)\n", 
               p_atual.nome, tempo_de_execucao, p_atual.tempo_restante - tempo_de_execucao);
        
        p_atual.tempo_restante -= tempo_de_execucao;

        if (p_atual.tempo_restante > 0) {
            enfileirar(fila, p_atual);
        } else {
            printf("--> %s finalizado.\n", p_atual.nome);
        }
    }

    printf("--- Todos os processos foram concluidos. ---\n");
}


int main() {
    Fila fila_de_processos;
    inicioFila(&fila_de_processos);

    int quantum = 3;

    Processo p1 = {"Processo A", 8};
    Processo p2 = {"Processo B", 4};
    Processo p3 = {"Processo C", 6};

    enfileirar(&fila_de_processos, p1);
    enfileirar(&fila_de_processos, p2);
    enfileirar(&fila_de_processos, p3);

    simularRoundRobin(&fila_de_processos, quantum);

    return 0;
}