// Arquivo: cliente.c
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h" // Inclui a nossa própria definição

void listar_clientes(PGconn* conn) {
    
    const char *query = "SELECT idCliente, nome, dataNascimento, cpf, endereco, telefone, idEquipamento_ativo FROM Clientes ORDER BY nome";

    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar clientes: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int num_rows = PQntuples(res);
    printf("\n--- Lista de Clientes (%d encontrados) ---\n", num_rows);
    
    // 2. Cabeçalho da tabela ATUALIZADO para incluir todos os campos
    printf("+-------+--------------------------------+-----------------+-----------------+--------------------------------+----------------------+---------------------+\n");
    printf("| %-5s | %-30s | %-15s | %-15s | %-30s | %-20s | %-19s |\n", "ID", "Nome", "Nascimento", "CPF", "Endereço", "Telefone", "ID Equip. Ativo");
    printf("+-------+--------------------------------+-----------------+-----------------+--------------------------------+----------------------+---------------------+\n");

    if (num_rows == 0) {
        printf("| Nenhum cliente cadastrado.                                                                                                                            |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            // 3. Exibição ATUALIZADA para imprimir todas as colunas na ordem correta
            printf("| %-5s | %-30s | %-15s | %-15s | %-30s | %-20s | %-19s |\n",
                   PQgetvalue(res, i, 0), // idCliente
                   PQgetvalue(res, i, 1), // nome
                   PQgetvalue(res, i, 2), // dataNascimento
                   PQgetvalue(res, i, 3), // cpf
                   PQgetvalue(res, i, 4), // endereco
                   PQgetvalue(res, i, 5), // telefone
                   PQgetvalue(res, i, 6)  // idEquipamento_ativo
            );
        }
    }
    printf("+-------+--------------------------------+-----------------+-----------------+--------------------------------+----------------------+---------------------+\n");

    PQclear(res);
}