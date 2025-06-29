// Arquivo: cliente.c
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h" // Inclui a nossa própria definição

void listar_clientes(PGconn* conn) {
    // 1. Prepara a query SQL
    const char *query = "SELECT idCliente, nome, cpf, telefone FROM Clientes ORDER BY nome";

    // 2. Executa a query
    // PQexec é a função principal da libpq para enviar um comando ao PostgreSQL
    PGresult* res = PQexec(conn, query);

    // 3. Verifica o resultado da execução da query
    // PGRES_TUPLES_OK significa que um SELECT foi executado com sucesso
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar clientes: %s\n", PQerrorMessage(conn));
        PQclear(res); // Libera a memória do resultado mesmo em caso de erro
        return;
    }

    // 4. Processa e exibe os resultados
    int num_rows = PQntuples(res);
    printf("\n--- Lista de Clientes (%d encontrados) ---\n", num_rows);
    printf("--------------------------------------------------------------------------\n");
    printf("%-5s | %-30s | %-15s | %-15s\n", "ID", "Nome", "CPF", "Telefone");
    printf("--------------------------------------------------------------------------\n");

    if (num_rows == 0) {
        printf("Nenhum cliente cadastrado.\n");
    } else {
        // Itera sobre cada linha (tupla) do resultado
        for (int i = 0; i < num_rows; i++) {
            // PQgetvalue obtém o valor de uma célula específica (linha, coluna) como uma string
            char* id = PQgetvalue(res, i, 0);
            char* nome = PQgetvalue(res, i, 1);
            char* cpf = PQgetvalue(res, i, 2);
            char* telefone = PQgetvalue(res, i, 3);
            printf("%-5s | %-30s | %-15s | %-15s\n", id, nome, telefone, cpf);
        }
    }
    printf("--------------------------------------------------------------------------\n");

    // 5. Libera a memória alocada para o resultado
    PQclear(res);
}