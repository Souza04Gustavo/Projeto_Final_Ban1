#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void inserir_escala(PGconn* conn) {
    char diaSemana[21];
    char horario_inicio[10]; // HH:MM:SS
    char horario_fim[10];

    printf("\n--- Inserir Nova Escala ---\n");

    printf("Dias da Semana (ex: Seg-Sex, Sab-Dom): ");
    fgets(diaSemana, sizeof(diaSemana), stdin);
    diaSemana[strcspn(diaSemana, "\n")] = 0;

    printf("Horário de Início (formato HH:MM:SS): ");
    fgets(horario_inicio, sizeof(horario_inicio), stdin);
    horario_inicio[strcspn(horario_inicio, "\n")] = 0;

    printf("Horário de Fim (formato HH:MM:SS): ");
    fgets(horario_fim, sizeof(horario_fim), stdin);
    horario_fim[strcspn(horario_fim, "\n")] = 0;

    const char *query = "INSERT INTO Escala (diaSemana, horario_inicio, horario_fim) VALUES ($1, $2, $3)";

    const char *paramValues[3];
    paramValues[0] = diaSemana;
    paramValues[1] = horario_inicio;
    paramValues[2] = horario_fim;

    PGresult* res = PQexecParams(conn, query, 3, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao inserir escala: %s\n", PQerrorMessage(conn));
    } else {
        printf("Escala inserida com sucesso!\n");
    }

    PQclear(res);
}

void remover_escala(PGconn* conn) {
    char idEscala[10];

    printf("\n--- Remover Escala ---\n");
    printf("Digite o ID da escala a ser removida: ");
    fgets(idEscala, sizeof(idEscala), stdin);
    idEscala[strcspn(idEscala, "\n")] = 0;

    const char *query = "DELETE FROM Escala WHERE idEscala = $1";
    
    const char *paramValues[1];
    paramValues[0] = idEscala;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao remover escala: %s\n", PQerrorMessage(conn));
    } else {
        if (atoi(PQcmdTuples(res)) == 0) {
            printf("Nenhuma escala encontrada com o ID %s.\n", idEscala);
        } else {
            printf("Escala com ID %s removida com sucesso!\n", idEscala);
        }
    }

    PQclear(res);
}