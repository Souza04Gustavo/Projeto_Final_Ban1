#include <stdio.h>
#include <stdlib.h>
#include "escala.h"

void listar_escalas(PGconn* conn) {
    const char *query = "SELECT idEscala, diaSemana, horario_inicio, horario_fim FROM Escala ORDER BY idEscala";
    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar escalas: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int num_rows = PQntuples(res);
    printf("\n--- Lista de Escalas (%d encontradas) ---\n", num_rows);
    printf("+-------+----------------------+----------------+---------------+\n");
    printf("| %-5s | %-20s | %-14s | %-13s |\n", "ID", "Dias da Semana", "Horário Início", "Horário Fim");
    printf("+-------+----------------------+----------------+---------------+\n");

    if (num_rows == 0) {
        printf("| Nenhuma escala cadastrada.                                         |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("| %-5s | %-20s | %-14s | %-13s |\n",
                   PQgetvalue(res, i, 0), // idEscala
                   PQgetvalue(res, i, 1), // diaSemana
                   PQgetvalue(res, i, 2), // horario_inicio
                   PQgetvalue(res, i, 3)  // horario_fim
            );
        }
    }
    printf("+-------+----------------------+----------------+---------------+\n");

    PQclear(res);
}