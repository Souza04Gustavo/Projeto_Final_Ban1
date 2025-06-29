#include <stdio.h>
#include <stdlib.h>
#include "anomalia.h"

void listar_anomalias(PGconn* conn) {
    const char *query = "SELECT idAnomalia, gravidade, localizacao, dataHora, idEquipamento, idFuncionario_registro FROM Anomalias ORDER BY dataHora DESC";
    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar anomalias: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int num_rows = PQntuples(res);
    printf("\n--- Histórico de Anomalias (%d encontradas) ---\n", num_rows);
    printf("+-------+-----------+--------------------------------+---------------------+-------------+--------------------+\n");
    printf("| %-5s | %-9s | %-30s | %-19s | %-11s | %-18s |\n", "ID", "Gravidade", "Localização", "Data e Hora", "ID Equip.", "ID Func. Registro");
    printf("+-------+-----------+--------------------------------+---------------------+-------------+--------------------+\n");

    if (num_rows == 0) {
        printf("| Nenhuma anomalia registrada.                                                                                 |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("| %-5s | %-9s | %-30s | %-19s | %-11s | %-18s |\n",
                   PQgetvalue(res, i, 0), // idAnomalia
                   PQgetvalue(res, i, 1), // gravidade
                   PQgetvalue(res, i, 2), // localizacao
                   PQgetvalue(res, i, 3), // dataHora
                   PQgetvalue(res, i, 4), // idEquipamento
                   PQgetvalue(res, i, 5)  // idFuncionario_registro
            );
        }
    }
    printf("+-------+-----------+--------------------------------+---------------------+-------------+--------------------+\n");

    PQclear(res);
}