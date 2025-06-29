#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipe.h"

void listar_equipes(PGconn* conn) {
    const char *query = "SELECT idEquipe, turno FROM Equipes ORDER BY idEquipe";
    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao listar equipes: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int num_rows = PQntuples(res);
    printf("\n--- Lista de Equipes (%d encontradas) ---\n", num_rows);
    printf("+-------+--------------------------------+\n");
    printf("| %-5s | %-30s |\n", "ID", "Turno");
    printf("+-------+--------------------------------+\n");

    if (num_rows == 0) {
        printf("| Nenhuma equipe cadastrada.             |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("| %-5s | %-30s |\n",
                   PQgetvalue(res, i, 0), // idEquipe
                   PQgetvalue(res, i, 1)  // turno
            );
        }
    }
    printf("+-------+--------------------------------+\n");

    PQclear(res);
}

void inserir_equipe(PGconn* conn) {
    char turno[51]; // Buffer para armazenar o nome do turno

    printf("\n--- Inserir Nova Equipe ---\n");
    printf("Digite o nome do turno (ex: Manhã, Tarde, Especial): ");

    // fgets é mais seguro que scanf para ler strings, pois evita buffer overflow.
    // Ele lê a linha inteira, incluindo o caractere de nova linha (\n).
    fgets(turno, sizeof(turno), stdin);

    // Remove o caractere de nova linha (\n) que o fgets captura no final da string.
    turno[strcspn(turno, "\n")] = 0;

    // A query usa $1 como um "placeholder" para o primeiro parâmetro que será enviado.
    const char *query = "INSERT INTO Equipes (turno) VALUES ($1)";

    // Preparamos um array com os valores dos parâmetros. Neste caso, só temos um.
    const char *paramValues[1];
    paramValues[0] = turno;

    // PQexecParams é a função segura para executar queries com parâmetros.
    // Ela separa o comando SQL dos dados, prevenindo SQL Injection.
    PGresult* res = PQexecParams(conn,
                                query,
                                 1,       // número de parâmetros
                                 NULL,    // tipos dos parâmetros (pode deixar o BD inferir)
                                 paramValues,
                                 NULL,    // comprimentos dos parâmetros (não necessário para texto)
                                 NULL,    // formatos dos parâmetros (0 para texto)
                                 0);      // o resultado da query virá em formato texto

    // PGRES_COMMAND_OK é o status de sucesso para comandos que não retornam linhas (INSERT, UPDATE, DELETE).
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao inserir equipe: %s\n", PQerrorMessage(conn));
    } else {
        printf("Equipe inserida com sucesso!\n");
    }

    PQclear(res);
}


void remover_equipe(PGconn* conn) {
    char idEquipe[10];

    printf("\n--- Remover Equipe ---\n");
    printf("Digite o ID da equipe a ser removida: ");
    fgets(idEquipe, sizeof(idEquipe), stdin);
    idEquipe[strcspn(idEquipe, "\n")] = 0;

    const char *query = "DELETE FROM Equipes WHERE idEquipe = $1";
    
    const char *paramValues[1];
    paramValues[0] = idEquipe;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao remover equipe: %s\n", PQerrorMessage(conn));
    } else {
        // PQcmdTuples() retorna uma string com o número de linhas afetadas pelo comando.
        // Usamos atoi() para converter essa string para um inteiro.
        if (atoi(PQcmdTuples(res)) == 0) {
            printf("Nenhuma equipe encontrada com o ID %s. Nada foi removido.\n", idEquipe);
        } else {
            printf("Equipe com ID %s removida com sucesso!\n", idEquipe);
        }
    }

    PQclear(res);
}