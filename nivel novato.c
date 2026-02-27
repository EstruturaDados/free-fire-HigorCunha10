#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Protótipos das funções
void inserirItem(struct Item mochila[], int *total);
void removerItem(struct Item mochila[], int *total);
void listarItens(struct Item mochila[], int total);
void buscarItem(struct Item mochila[], int total);

int main() {
    struct Item mochila[10];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n--- MOCHILA DE LOOT ---\n");
        printf("1. Cadastrar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 5:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}

// Função para cadastrar itens (Limite de 10)
void inserirItem(struct Item mochila[], int *total) {
    if (*total >= 10) {
        printf("Erro: Mochila cheia!\n");
        return;
    }

    printf("Nome do item: ");
    fgets(mochila[*total].nome, 30, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = 0;

    printf("Tipo (arma/municao/cura): ");
    fgets(mochila[*total].tipo, 20, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    getchar();

    (*total)++;
    printf("Item cadastrado com sucesso!\n");
}

// Função para listar todos os itens registrados
void listarItens(struct Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila esta vazia.\n");
        return;
    }

    printf("\n--- ITENS NA MOCHILA ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d. Nome: %s | Tipo: %s | Qtd: %d\n", 
                i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função de busca sequencial pelo nome
void buscarItem(struct Item mochila[], int total) {
    char alvo[30];
    printf("Digite o nome do item para busca: ");
    fgets(alvo, 30, stdin);
    alvo[strcspn(alvo, "\n")] = 0;

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, alvo) == 0) {
            printf("Item encontrado! Tipo: %s | Quantidade: %d\n", 
                    mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item nao encontrado na mochila.\n");
}

// Função para remover item e reorganizar o vetor
void removerItem(struct Item mochila[], int *total) {
    char alvo[30];
    printf("Nome do item para excluir: ");
    fgets(alvo, 30, stdin);
    alvo[strcspn(alvo, "\n")] = 0;

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, alvo) == 0) {
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Erro: Item nao localizado.\n");
};
