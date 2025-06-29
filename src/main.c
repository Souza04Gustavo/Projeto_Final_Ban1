// para compilar:
// gcc -o monitor_app src/main.c src/database.c src/cliente.c src/funcionario.c src/equipe.c src/equipamento.c src/escala.c src/anomalia.c src/relatorios.c -Iinclude -I/usr/include/postgresql -lpq

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
#include "relatorios.h"

void limpar_buffer_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void exibir_menu() {
    printf("\n---- SISTEMA DE MONITORAMENTO DE IDOSOS ----\n");
    printf("1. Listar todas as tuplas das tabelas\n");
    printf("2. Inserir uma tupla em uma tabela\n");
    printf("3. Remover uma tupla de uma tabela\n");
    printf("4. Listar equipamento ativo de cada cliente [consulta com JUNÇÃO (JOIN)]\n");
    printf("5. Contar total de anomalias por cliente [consulta com SUBQUERY e AGREGAÇÃO]\n");
    printf("0. Sair\n");
    printf("----------------------------------------------\n");
    printf("Escolha uma opção: ");
}

void submenu_consulta_tuplas(PGconn* conn) {
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

    int sub_opcao = -1;
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
                
}

void submenu_inserir(PGconn* conn) {
    int opcao = -1;
    while(opcao != 0) {
        printf("\n--- Em qual tabela você deseja INSERIR? ---\n");
        printf("1. Equipe\n");
        printf("2. Cliente\n");
        printf("3. Funcionário\n");
        printf("4. Equipamento\n");
        printf("5. Anomalia\n");
        printf("6. Escala\n");
        printf("0. Voltar ao menu principal\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        limpar_buffer_teclado();

        switch(opcao) {
            case 1: inserir_equipe(conn); break;
            case 2: inserir_cliente(conn); break;
            case 3: inserir_funcionario(conn); break;
            case 4: inserir_equipamento(conn); break;
            case 5: inserir_anomalia(conn); break;
            case 6: inserir_escala(conn); break;
            case 0: printf("Retornando...\n"); break;
            default: printf("Opção inválida!\n");
        }
    }
}

void submenu_remover(PGconn* conn) {
    int opcao = -1;
    while(opcao != 0) {
        printf("\n--- De qual tabela você deseja REMOVER? ---\n");
        printf("1. Equipe\n");
        printf("2. Cliente\n");
        printf("3. Funcionário\n");
        printf("4. Equipamento\n");
        printf("5. Anomalia\n");
        printf("6. Escala\n");
        printf("0. Voltar ao menu principal\n");
        printf("-------------------------------------------\n");
        printf("Escolha uma opção: ");
        
        scanf("%d", &opcao);
        limpar_buffer_teclado();

        switch(opcao) {
            case 1: remover_equipe(conn); break;
            case 2: remover_cliente(conn); break;
            case 3: remover_funcionario(conn); break;
            case 4: remover_equipamento(conn); break;
            case 5: remover_anomalia(conn); break;
            case 6: remover_escala(conn); break;
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
                submenu_consulta_tuplas(conn);
                break;
            case 2:
                submenu_inserir(conn);
                break;
            case 3:
                submenu_remover(conn);
                break;
            case 4:
                relatorio_clientes_equipamentos(conn);
                break;
            case 5:
                relatorio_anomalias_por_cliente(conn);
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