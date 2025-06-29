// Arquivo: main.c
#include <stdio.h>
#include <stdlib.h>
#include "database.h" // Inclui nosso módulo de banco de dados
#include "cliente.h"


void exibir_menu() {
    printf("\n---- SISTEMA DE MONITORAMENTO DE IDOSOS ----\n");
    printf("1. Listar todos os clientes\n");
    printf("2. Adicionar novo cliente (ainda não implementado)\n");
    printf("3. Remover cliente (ainda não implementado)\n");
    printf("0. Sair\n");
    printf("----------------------------------------------\n");
    printf("Escolha uma opção: ");
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

        // Limpa o buffer de entrada para evitar problemas com leituras futuras
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcao) {
            case 1:
                listar_clientes(conn);
                break;
            case 2:
                printf("Funcionalidade ainda não implementada.\n");
                break;
            case 3:
                printf("Funcionalidade ainda não implementada.\n");
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