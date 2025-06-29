#include <stdio.h>
#include <stdlib.h>
#include "equipamento.h"

void listar_equipamentos(PGconn* conn) {
    const char *query = "SELECT idEquipamento, modelo, dataValidade, ultimaManutencao FROM Equipamento ORDER BY idEquipamento";
    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar equipamentos: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int num_rows = PQntuples(res);
    printf("\n--- Lista de Equipamentos (%d encontrados) ---\n", num_rows);
    printf("+-------+---------------------------+----------------+--------------------+\n");
    printf("| %-5s | %-25s | %-14s | %-18s |\n", "ID", "Modelo", "Data Validade", "Última Manutenção");
    printf("+-------+---------------------------+----------------+--------------------+\n");

    if (num_rows == 0) {
        printf("| Nenhum equipamento cadastrado.                                               |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("| %-5s | %-25s | %-14s | %-18s |\n",
                   PQgetvalue(res, i, 0), // idEquipamento
                   PQgetvalue(res, i, 1), // modelo
                   PQgetvalue(res, i, 2), // dataValidade
                   PQgetvalue(res, i, 3)  // ultimaManutencao
            );
        }
    }
    printf("+-------+---------------------------+----------------+--------------------+\n");

    PQclear(res);
}