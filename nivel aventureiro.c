#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição das estruturas
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

struct No {
    Item dados;
    struct No* proximo;
};

// Variável global para contar comparações nas buscas
int comparacoes = 0;

// Funções para Vetor
void inserirVetor(Item mochila[], int *total, char nome[], char tipo[], int qtd);
void listarVetor(Item mochila[], int total);
int buscaSequencialVetor(Item mochila[], int total, char alvo[]);
void ordenarVetor(Item mochila[], int total);
int buscaBinariaVetor(Item mochila[], int total, char alvo[]);
void removerVetor(Item mochila[], int *total, char alvo[]);

// Funções para Lista Encadeada
struct No* inserirLista(struct No* inicio, Item novoItem);
void listarLista(struct No* inicio);
int buscaSequencialLista(struct No* inicio, char alvo[]);
struct No* removerLista(struct No* inicio, char alvo[]);

int main() {
    Item mochilaVetor[10];
    int totalVetor = 0;
    struct No* mochilaLista = NULL;
    int opcao, subOpcao, resultado, qtd;
    char nome[30], tipo[20];

    do {
        printf("\n--- SISTEMA DE MOCHILA ---\n");
        printf("1. Trabalhar com VETOR (Sequencial)\n");
        printf("2. Trabalhar com LISTA (Encadeada)\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            printf("\n[VETOR] 1.Inserir 2.Remover 3.Listar 4.Busca Seq. 5.Ordenar e Busca Binaria: ");
            scanf("%d", &subOpcao);
            getchar();

            if (subOpcao == 1) {
                printf("Nome: "); fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                printf("Tipo: "); fgets(tipo, 20, stdin); tipo[strcspn(tipo, "\n")] = 0;
                printf("Qtd: "); scanf("%d", &qtd);
                inserirVetor(mochilaVetor, &totalVetor, nome, tipo, qtd);
            } 
            else if (subOpcao == 2) {
                printf("Nome para remover: "); fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                removerVetor(mochilaVetor, &totalVetor, nome);
            }
            else if (subOpcao == 3) listarVetor(mochilaVetor, totalVetor);
            else if (subOpcao == 4) {
                printf("Busca: "); fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                comparacoes = 0;
                resultado = buscaSequencialVetor(mochilaVetor, totalVetor, nome);
                printf("Resultado: %d | Comparacoes: %d\n", resultado, comparacoes);
            }
            else if (subOpcao == 5) {
                ordenarVetor(mochilaVetor, totalVetor);
                printf("Vetor ordenado! Nome para Busca Binaria: ");
                fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                comparacoes = 0;
                resultado = buscaBinariaVetor(mochilaVetor, totalVetor, nome);
                printf("Resultado: %d | Comparacoes: %d\n", resultado, comparacoes);
            }
        } 
        else if (opcao == 2) {
            printf("\n[LISTA] 1.Inserir 2.Remover 3.Listar 4.Busca Seq: ");
            scanf("%d", &subOpcao);
            getchar();

            if (subOpcao == 1) {
                Item temp;
                printf("Nome: "); fgets(temp.nome, 30, stdin); temp.nome[strcspn(temp.nome, "\n")] = 0;
                printf("Tipo: "); fgets(temp.tipo, 20, stdin); temp.tipo[strcspn(temp.tipo, "\n")] = 0;
                printf("Qtd: "); scanf("%d", &temp.quantidade);
                mochilaLista = inserirLista(mochilaLista, temp);
            }
            else if (subOpcao == 2) {
                printf("Nome para remover: "); fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                mochilaLista = removerLista(mochilaLista, nome);
            }
            else if (subOpcao == 3) listarLista(mochilaLista);
            else if (subOpcao == 4) {
                printf("Busca: "); fgets(nome, 30, stdin); nome[strcspn(nome, "\n")] = 0;
                comparacoes = 0;
                resultado = buscaSequencialLista(mochilaLista, nome);
                printf("Encontrado (1-Sim/0-Nao): %d | Comparacoes: %d\n", resultado, comparacoes);
            }
        }
    } while (opcao != 3);

    return 0;
}

// Implementação Vetor
void inserirVetor(Item mochila[], int *total, char nome[], char tipo[], int qtd) {
    if (*total < 10) {
        strcpy(mochila[*total].nome, nome);
        strcpy(mochila[*total].tipo, tipo);
        mochila[*total].quantidade = qtd;
        (*total)++;
    }
}

void listarVetor(Item mochila[], int total) {
    for (int i = 0; i < total; i++)
        printf("[%d] %s (%s) x%d\n", i, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
}

int buscaSequencialVetor(Item mochila[], int total, char alvo[]) {
    for (int i = 0; i < total; i++) {
        comparacoes++;
        if (strcmp(mochila[i].nome, alvo) == 0) return i;
    }
    return -1;
}

void ordenarVetor(Item mochila[], int total) {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
}

int buscaBinariaVetor(Item mochila[], int total, char alvo[]) {
    int ini = 0, fim = total - 1;
    while (ini <= fim) {
        comparacoes++;
        int meio = (ini + fim) / 2;
        int res = strcmp(mochila[meio].nome, alvo);
        if (res == 0) return meio;
        if (res < 0) ini = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void removerVetor(Item mochila[], int *total, char alvo[]) {
    int pos = buscaSequencialVetor(mochila, *total, alvo);
    if (pos != -1) {
        for (int i = pos; i < *total - 1; i++) mochila[i] = mochila[i+1];
        (*total)--;
    }
}

// Implementação Lista Encadeada
struct No* inserirLista(struct No* inicio, Item novoItem) {
    struct No* novo = (struct No*) malloc(sizeof(struct No));
    novo->dados = novoItem;
    novo->proximo = inicio;
    return novo;
}

void listarLista(struct No* inicio) {
    struct No* atual = inicio;
    while (atual != NULL) {
        printf("%s (%s) x%d -> ", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

int buscaSequencialLista(struct No* inicio, char alvo[]) {
    struct No* atual = inicio;
    while (atual != NULL) {
        comparacoes++;
        if (strcmp(atual->dados.nome, alvo) == 0) return 1;
        atual = atual->proximo;
    }
    return 0;
}

struct No* removerLista(struct No* inicio, char alvo[]) {
    struct No *atual = inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, alvo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) return inicio;
    if (anterior == NULL) inicio = atual->proximo;
    else anterior->proximo = atual->proximo;
    free(atual);
    return inicio;
};
