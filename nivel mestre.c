#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis para análise de desempenho
int comparacoes = 0;

// Função auxiliar para troca de posição
void trocar(Componente* a, Componente* b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// Ordenação por Nome (String)
void bubbleSortNome(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                trocar(&lista[j], &lista[j + 1]);
            }
        }
    }
}

// Ordenação por Tipo (String)
void insertionSortTipo(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = lista[i];
        int j = i - 1;
        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            lista[j + 1] = lista[j];
            j--;
        }
        if (j >= 0) comparacoes++; // Conta a comparação que falhou no while
        lista[j + 1] = chave;
    }
}

// Ordenação por Prioridade (Inteiro)
void selectionSortPrioridade(Componente lista[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (lista[j].prioridade < lista[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            trocar(&lista[i], &lista[min]);
        }
    }
}

// Busca Binária por Nome
int buscaBinariaNome(Componente lista[], int n, char alvo[]) {
    int inicio = 0, fim = n - 1;
    int compBusca = 0;
    while (inicio <= fim) {
        compBusca++;
        int meio = (inicio + fim) / 2;
        int res = strcmp(lista[meio].nome, alvo);
        if (res == 0) {
            printf("Busca concluida em %d comparacoes.\n", compBusca);
            return meio;
        }
        if (res < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void mostrarComponentes(Componente lista[], int n) {
    printf("\n--- LISTA DE COMPONENTES ---\n");
    for (int i = 0; i < n; i++) {
        printf("[%02d] Nome: %-15s | Tipo: %-10s | Prioridade: %d\n", 
               i, lista[i].nome, lista[i].tipo, lista[i].prioridade);
    }
}

int main() {
    Componente torre[20];
    int n = 0, opcao, ordenadoPorNome = 0;
    clock_t t_ini, t_fim;
    double tempo_cpu;

    // Cadastro inicial simplificado para o teste
    printf("Quantos componentes cadastrar (max 20)? ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("Item %d - Nome: ", i + 1);
        fgets(torre[i].nome, 30, stdin);
        torre[i].nome[strcspn(torre[i].nome, "\n")] = 0;
        printf("Item %d - Tipo: ", i + 1);
        fgets(torre[i].tipo, 20, stdin);
        torre[i].tipo[strcspn(torre[i].tipo, "\n")] = 0;
        printf("Item %d - Prioridade (1-10): ", i + 1);
        scanf("%d", &torre[i].prioridade);
        getchar();
    }

    do {
        printf("\n--- MENU ESTRATEGICO ---\n");
        printf("1. Ordenar por Nome (Bubble)\n2. Ordenar por Tipo (Insertion)\n");
        printf("3. Ordenar por Prioridade (Selection)\n4. Buscar Componente-Chave (Binaria)\n");
        printf("5. Listar e Sair\nEscolha: ");
        scanf("%d", &opcao);
        getchar();

        t_ini = clock();
        switch (opcao) {
            case 1:
                bubbleSortNome(torre, n);
                ordenadoPorNome = 1;
                break;
            case 2:
                insertionSortTipo(torre, n);
                ordenadoPorNome = 0;
                break;
            case 3:
                selectionSortPrioridade(torre, n);
                ordenadoPorNome = 0;
                break;
            case 4:
                if (!ordenadoPorNome) {
                    printf("Erro: Ordene por NOME primeiro!\n");
                    continue;
                }
                char alvo[30];
                printf("Nome do componente: ");
                fgets(alvo, 30, stdin);
                alvo[strcspn(alvo, "\n")] = 0;
                int pos = buscaBinariaNome(torre, n, alvo);
                if (pos != -1) printf("Componente encontrado na posicao %d!\n", pos);
                else printf("Componente nao localizado.\n");
                continue;
        }
        t_fim = clock();
        tempo_cpu = ((double)(t_fim - t_ini)) / CLOCKS_PER_SEC;

        if (opcao >= 1 && opcao <= 3) {
            printf("\nOrdenacao concluida!\nComparacoes: %d\nTempo: %f segundos\n", comparacoes, tempo_cpu);
            mostrarComponentes(torre, n);
        }

    } while (opcao != 5);

    return 0;
};
