#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

// --- Definições Globais ---
#define CAPACIDADE_MAXIMA 10
#define TAMANHO_STRING 50

// --- Estrutura (Struct) ---
typedef struct {
    char nome[TAMANHO_STRING];
    char tipo[TAMANHO_STRING];
    int quantidade;
    int ativo; // 0 = Inativo, 1 = Ativo
} ItemMochila;

// --- Variáveis Globais ---
ItemMochila mochila[CAPACIDADE_MAXIMA];
int total_itens_ativos = 0;

// --- Protótipos das Funções ---
void mostrar_menu();
void adicionar_item();
void remover_item();
void listar_itens();
void limpar_buffer();


// --- Função Auxiliar: Limpar o Buffer ---
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


// --- Função: Mostrar Menu ---
void mostrar_menu() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("==================================\n");
    printf("     MOCHILA DE SOBREVIVENCIA\n");
    printf("==================================\n");
    printf("1. Adicionar Item\n");
    printf("2. Remover Item (pelo nome)\n");
    printf("3. Listar Itens\n");
    printf("0. Sair\n");
    printf("----------------------------------\n");
    printf("Espaços Ocupados: %d/%d\n", total_itens_ativos, CAPACIDADE_MAXIMA);
    printf("==================================\n");
    printf("Escolha uma opção: ");
}


// --- Função: Adicionar Item ---
void adicionar_item() {
    int i;
    int slot_livre = -1; 

    // Procura por um slot livre
    for (i = 0; i < CAPACIDADE_MAXIMA; i++) {
        if (mochila[i].ativo == 0) {
            slot_livre = i;
            break; 
        }
    }

    if (slot_livre == -1) {
        printf("\nMochila Cheia! Capacidade máxima (%d) atingida.\n", CAPACIDADE_MAXIMA);
        printf("Pressione ENTER para continuar...\n");
        limpar_buffer();
        return;
    }

    printf("\n--- Adicionar Item ---\n");

    printf("Nome do Item: ");
    fgets(mochila[slot_livre].nome, TAMANHO_STRING, stdin);
    mochila[slot_livre].nome[strcspn(mochila[slot_livre].nome, "\n")] = '\0'; 

    printf("Tipo do Item (Ex: Consumível, Armadura): ");
    fgets(mochila[slot_livre].tipo, TAMANHO_STRING, stdin);
    mochila[slot_livre].tipo[strcspn(mochila[slot_livre].tipo, "\n")] = '\0'; 

    printf("Quantidade: ");
    if (scanf("%d", &mochila[slot_livre].quantidade) != 1 || mochila[slot_livre].quantidade <= 0) {
        printf("Quantidade inválida. Item não adicionado.\n");
        mochila[slot_livre].ativo = 0;
        limpar_buffer(); 
        return;
    }

    mochila[slot_livre].ativo = 1; 
    total_itens_ativos++;
    printf("\nItem '%s' adicionado com sucesso na posição %d.\n", mochila[slot_livre].nome, slot_livre + 1);
    printf("Pressione ENTER para continuar...");
    limpar_buffer();
}


// --- Função: Remover Item 
void remover_item() {
    char nome_remover[TAMANHO_STRING];
    int i;
    int encontrado = 0; 

    printf("\n--- Remover Item ---\n");

    printf("Digite o NOME do item a remover: ");
         
    fgets(nome_remover, TAMANHO_STRING, stdin);
    nome_remover[strcspn(nome_remover, "\n")] = '\0'; 

    // Procura e remoção
    for (i = 0; i < CAPACIDADE_MAXIMA; i++) {
        if (mochila[i].ativo == 1 && strcmp(mochila[i].nome, nome_remover) == 0) {
            mochila[i].ativo = 0;
            total_itens_ativos--;
            encontrado = 1;
            printf("\nItem '%s' removido com sucesso.\n", nome_remover);
            break; 
        }
    }

    if (!encontrado) {
        printf("\nItem '%s' não encontrado na mochila.\n", nome_remover);
    }

    printf("Pressione ENTER para continuar...\n");
    limpar_buffer(); 
}


// --- Função: Listar Itens ---
void listar_itens() {
    int i;
    
    printf("\n--- Itens Cadastrados na Mochila ---\n");

    if (total_itens_ativos == 0) {
        printf("\n>> A mochila está vazia. Adicione itens (Opção 1).\n");
        printf("\nPressione ENTER para continuar...\n");
        limpar_buffer();
        return;
    }
    
    printf("+-------+----------------------+-------------------+----------+\n");
    printf("| ITEM  | NOME                 | TIPO              | QUANT.   |\n");
    printf("+-------+----------------------+-------------------+----------+\n");

    for (i = 0; i < CAPACIDADE_MAXIMA; i++) {
        if (mochila[i].ativo == 1) {
            printf("| %-5d | %-20s | %-17s | %-8d |\n",
                   i + 1, 
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
        }
    }
    printf("+-------+----------------------+-------------------+----------+\n");
    
    printf("Pressione ENTER para continuar...\n");
    limpar_buffer(); 
}


// --- Função Principal (Main) ---
int main() {
    int opcao;
    
    for (int i = 0; i < CAPACIDADE_MAXIMA; i++) {
        mochila[i].ativo = 0;
    }

    do {
        mostrar_menu();

        if (scanf("%d", &opcao) != 1) {
            printf("\nOpção inválida. Digite apenas números.\n");
            opcao = -1; 
            limpar_buffer(); 
            continue; 
        }

        // Limpa o '\n' após a leitura da opção do menu
        limpar_buffer(); 

        switch (opcao) {
            case 1:
                adicionar_item();
                break;
            case 2:
                remover_item();
                break;
            case 3:
                listar_itens();
                break;
            case 0:
                printf("\nSaindo do Gerenciador de Mochila. Até logo!\n");
                break;
            default:
                printf("\nOpção desconhecida. Tente novamente.\n");
                printf("Pressione ENTER para continuar...");
                limpar_buffer();
                break;
        }
        
    } while (opcao != 0); 

    return 0;
}