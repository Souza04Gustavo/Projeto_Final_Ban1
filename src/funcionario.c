#include <stdio.h>
#include <stdlib.h>
#include "funcionario.h"

void listar_funcionarios(PGconn* conn) {
    const char *query = "SELECT idFuncionario, nome, salario, email, idEquipe, idEscala FROM Funcionarios ORDER BY nome";
    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar funcionários: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int num_rows = PQntuples(res);
    printf("\n--- Lista de Funcionários (%d encontrados) ---\n", num_rows);
    printf("+-------+--------------------------------+------------+--------------------------------+-----------+-----------+\n");
    printf("| %-5s | %-30s | %-10s | %-30s | %-9s | %-9s |\n", "ID", "Nome", "Salário", "Email", "ID Equipe", "ID Escala");
    printf("+-------+--------------------------------+------------+--------------------------------+-----------+-----------+\n");

    if (num_rows == 0) {
        printf("| Nenhum funcionário cadastrado.                                                                            |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("| %-5s | %-30s | %-10s | %-30s | %-9s | %-9s |\n",
                   PQgetvalue(res, i, 0), // idFuncionario
                   PQgetvalue(res, i, 1), // nome
                   PQgetvalue(res, i, 2), // salario
                   PQgetvalue(res, i, 3), // email
                   PQgetvalue(res, i, 4), // idEquipe
                   PQgetvalue(res, i, 5)  // idEscala
            );
        }
    }
    printf("+-------+--------------------------------+------------+--------------------------------+-----------+-----------+\n");

    PQclear(res);
}