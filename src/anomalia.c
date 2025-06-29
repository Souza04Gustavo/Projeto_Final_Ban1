#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "anomalia.h"
#include "equipamento.h" // Incluído para ajudar o usuário
#include "funcionario.h" // Incluído para ajudar o usuário

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


void inserir_anomalia(PGconn* conn) {
    char gravidade[51];
    char localizacao[256];
    char idEquipamento[10];
    char idFuncionario[10];

    printf("\n--- Registrar Nova Anomalia ---\n");

    printf("Equipamentos ativos (para referência):\n");
    listar_equipamentos(conn);
    printf("Funcionários disponíveis (para referência):\n");
    listar_funcionarios(conn);

    printf("Gravidade (Baixa, Média, Alta): ");
    fgets(gravidade, sizeof(gravidade), stdin);
    gravidade[strcspn(gravidade, "\n")] = 0;

    printf("Localização do evento: ");
    fgets(localizacao, sizeof(localizacao), stdin);
    localizacao[strcspn(localizacao, "\n")] = 0;

    printf("ID do Equipamento que gerou o alerta: ");
    fgets(idEquipamento, sizeof(idEquipamento), stdin);
    idEquipamento[strcspn(idEquipamento, "\n")] = 0;

    printf("ID do Funcionário que está registrando: ");
    fgets(idFuncionario, sizeof(idFuncionario), stdin);
    idFuncionario[strcspn(idFuncionario, "\n")] = 0;

    // A dataHora será inserida automaticamente pelo banco de dados (DEFAULT CURRENT_TIMESTAMP)
    const char *query = "INSERT INTO Anomalias (gravidade, localizacao, idEquipamento, idFuncionario_registro) VALUES ($1, $2, $3, $4)";

    const char *paramValues[4];
    paramValues[0] = gravidade;
    paramValues[1] = localizacao;
    paramValues[2] = idEquipamento;
    paramValues[3] = idFuncionario;

    PGresult* res = PQexecParams(conn, query, 4, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao registrar anomalia: %s\n", PQerrorMessage(conn));
    } else {
        printf("Anomalia registrada com sucesso!\n");
    }

    PQclear(res);
}


void remover_anomalia(PGconn* conn) {
    char idAnomalia[10];

    printf("\n--- Remover Registro de Anomalia ---\n");
    printf("Digite o ID da anomalia a ser removida: ");
    fgets(idAnomalia, sizeof(idAnomalia), stdin);
    idAnomalia[strcspn(idAnomalia, "\n")] = 0;

    const char *query = "DELETE FROM Anomalias WHERE idAnomalia = $1";
    
    const char *paramValues[1];
    paramValues[0] = idAnomalia;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao remover anomalia: %s\n", PQerrorMessage(conn));
    } else {
        if (atoi(PQcmdTuples(res)) == 0) {
            printf("Nenhuma anomalia encontrada com o ID %s.\n", idAnomalia);
        } else {
            printf("Anomalia com ID %s removida com sucesso!\n", idAnomalia);
        }
    }

    PQclear(res);
}