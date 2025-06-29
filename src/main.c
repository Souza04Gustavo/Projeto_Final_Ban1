// para compilar:
// gcc -o monitor_app src/main.c src/database.c src/cliente.c src/funcionario.c src/equipe.c src/equipamento.c src/escala.c src/anomalia.c -Iinclude -I/usr/include/postgresql -lpq
// para executar:
// ./monitor_app

#include <stdio.h>
#include <stdlib.h>
#include "database.h"
#include "cliente.h"
#include "funcionario.h"
#include "equipe.h"
#include "equipamento.h"
#include "escala.h"
#include "anomalia.h"


void limpar_buffer_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void exibir_menu() {
    printf("\n---- SISTEMA DE MONITORAMENTO DE IDOSOS ----\n");
    printf("1. Listar todas as tuplas das tabelas\n");
    printf("2. Inserir uma tupla em uma tabela\n");
    printf("3. Remover uma tupla de uma tabela\n");
    printf("4. Executar consulta com JUNÇÃO (JOIN)\n");
    printf("5. Executar consulta com SUBQUERY e AGREGAÇÃO\n");
    printf("0. Sair\n");
    printf("----------------------------------------------\n");
    printf("Escolha uma opção: ");
}


void exibir_submenu_tuplas() {
    printf("\n---- SUBMENU SELEÇÃO DE TODAS AS TUPLAS DE UMA TABELA ----\n");
    printf("1. anomalias\n");
    printf("2. clientes\n");
    printf("3. equipamento\n");
    printf("4. equipes\n");
    printf("5. escala\n");
    printf("6. funcionarios\n");
    printf("0. Voltar ao menu principal\n");
    printf("----------------------------------------------\n");
    printf("Escolha uma opção: ");
}

void menu_gerenciar_equipes(PGconn* conn) {
    int opcao = -1;
    while(opcao != 0) {
        printf("\n---- Gerenciar Equipes ----\n");
        printf("1. Listar todas as equipes\n");
        printf("2. Adicionar nova equipe\n");
        printf("3. Remover equipe\n");
        printf("0. Voltar ao menu principal\n");
        printf("---------------------------\n");
        printf("Escolha uma opção: ");

        // Lê a opção do usuário
        scanf("%d", &opcao);

        // Limpa manualmente o buffer de entrada do teclado
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch(opcao) {
            case 1:
                listar_equipes(conn);
                break;
            case 2:
                inserir_equipe(conn);
                break;
            case 3:
                remover_equipe(conn);
                break;
            case 0:
                printf("Retornando ao menu principal...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }
}

void submenu_inserir(PGconn* conn) {
    int opcao = -1;
    while(opcao != 0) {
        printf("\n--- Em qual tabela você deseja INSERIR? ---\n");
        // Opções para inserção...
        printf("1. Equipe\n");
        // Adicionar aqui as outras opções (Cliente, Funcionário, etc.)
        printf("0. Voltar ao menu principal\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        limpar_buffer_teclado();

        switch(opcao) {
            case 1: inserir_equipe(conn); break;
            // case 2: inserir_cliente(conn); break; // A ser implementado
            // ...
            case 0: printf("Retornando...\n"); break;
            default: printf("Opção inválida!\n");
        }
    }
}

void submenu_remover(PGconn* conn) {
    int opcao = -1;
    while(opcao != 0) {
        printf("\n--- De qual tabela você deseja REMOVER? ---\n");
        // Opções para remoção...
        printf("1. Equipe\n");
        printf("0. Voltar ao menu principal\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        limpar_buffer_teclado();

        switch(opcao) {
            case 1: remover_equipe(conn); break;
            // case 2: remover_cliente(conn); break; // A ser implementado
            // ...
            case 0: printf("Retornando...\n"); break;
            default: printf("Opção inválida!\n");
        }
    }
}


int main() {

    PGconn* conn = conectar_bd();
    if (conn == NULL) {
        return 1;  // nao conectou ao BD
    }

    int opcao = -1;
    while(opcao != 0) {
        exibir_menu();
        scanf("%d", &opcao);
        limpar_buffer_teclado();

        switch (opcao) {
            case 1:
                int sub_opcao = -1;
                exibir_submenu_tuplas();
                scanf("%d", &sub_opcao);
                limpar_buffer_teclado();
                
                switch(sub_opcao) {
                    case 1:
                        printf("Listando anomalias...\n");
                        listar_anomalias(conn);
                        break;
                    case 2:
                        printf("Listando clientes...\n");
                        listar_clientes(conn);
                        break;
                    case 3:
                        printf("Listando equipamentos...\n");
                        listar_equipamentos(conn);
                        break;
                    case 4:
                        printf("Listando equipes...\n");
                        listar_equipes(conn);
                        break;
                    case 5:
                        printf("Listando escalas...\n");
                        listar_escalas(conn);
                        break;
                    case 6:
                        printf("Listando funcionários...\n");
                        listar_funcionarios(conn);
                        break;
                    case 0:
                        printf("Voltando ao menu principal...\n");
                        break;
                    default:
                        printf("Opção inválida! Tente novamente.\n");
                }
                
                break;
            
            case 2:
                submenu_inserir(conn);
                break;
            case 3:
                submenu_remover(conn);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    desconectar_bd(conn);
    printf("Aplicação finalizada.\n");
    return 0;
}