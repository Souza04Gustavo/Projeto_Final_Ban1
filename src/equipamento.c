#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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



void inserir_equipamento(PGconn* conn) {
    char modelo[51];
    char dataValidade[12]; // AAAA-MM-DD
    char ultimaManutencao[12];

    printf("\n--- Inserir Novo Equipamento ---\n");

    printf("Modelo do equipamento: ");
    fgets(modelo, sizeof(modelo), stdin);
    modelo[strcspn(modelo, "\n")] = 0;

    printf("Data de Validade (formato AAAA-MM-DD): ");
    fgets(dataValidade, sizeof(dataValidade), stdin);
    dataValidade[strcspn(dataValidade, "\n")] = 0;

    printf("Data da Última Manutenção (AAAA-MM-DD, deixe em branco se não houver): ");
    fgets(ultimaManutencao, sizeof(ultimaManutencao), stdin);
    ultimaManutencao[strcspn(ultimaManutencao, "\n")] = 0;

    const char *query = "INSERT INTO Equipamento (modelo, dataValidade, ultimaManutencao) VALUES ($1, $2, $3)";

    const char *paramValues[3];
    paramValues[0] = modelo;
    paramValues[1] = dataValidade;
    paramValues[2] = (strlen(ultimaManutencao) > 0) ? ultimaManutencao : NULL;

    PGresult* res = PQexecParams(conn, query, 3, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao inserir equipamento: %s\n", PQerrorMessage(conn));
    } else {
        printf("Equipamento inserido com sucesso!\n");
    }

    PQclear(res);
}

void remover_equipamento(PGconn* conn) {
    char idEquipamento[10];

    printf("\n--- Remover Equipamento ---\n");
    printf("Digite o ID do equipamento a ser removido: ");
    fgets(idEquipamento, sizeof(idEquipamento), stdin);
    idEquipamento[strcspn(idEquipamento, "\n")] = 0;

    const char *query = "DELETE FROM Equipamento WHERE idEquipamento = $1";
    
    const char *paramValues[1];
    paramValues[0] = idEquipamento;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao remover equipamento: %s\n", PQerrorMessage(conn));
    } else {
        if (atoi(PQcmdTuples(res)) == 0) {
            printf("Nenhum equipamento encontrado com o ID %s.\n", idEquipamento);
        } else {
            printf("Equipamento com ID %s removido com sucesso!\n", idEquipamento);
        }
    }

    PQclear(res);
}