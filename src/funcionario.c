#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.h"
#include "equipe.h"  // Incluímos para poder listar as equipes e ajudar o usuário
#include "escala.h" // Incluímos para poder listar as escalas

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

void inserir_funcionario(PGconn* conn) {
    char nome[101];
    char salario[20];
    char email[101];
    char idEquipe[10];
    char idEscala[10];

    printf("\n--- Inserir Novo Funcionário ---\n");

    printf("Equipes disponíveis:\n");
    listar_equipes(conn);
    printf("Escalas disponíveis:\n");
    listar_escalas(conn);

    printf("Nome completo: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Salário (ex: 3500.00): ");
    fgets(salario, sizeof(salario), stdin);
    salario[strcspn(salario, "\n")] = 0;

    printf("Email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf("ID da Equipe: ");
    fgets(idEquipe, sizeof(idEquipe), stdin);
    idEquipe[strcspn(idEquipe, "\n")] = 0;

    printf("ID da Escala: ");
    fgets(idEscala, sizeof(idEscala), stdin);
    idEscala[strcspn(idEscala, "\n")] = 0;

    const char *query = "INSERT INTO Funcionarios (nome, salario, email, idEquipe, idEscala) VALUES ($1, $2, $3, $4, $5)";

    const char *paramValues[5];
    paramValues[0] = nome;
    paramValues[1] = salario;
    paramValues[2] = email;
    paramValues[3] = idEquipe;
    paramValues[4] = idEscala;

    PGresult* res = PQexecParams(conn, query, 5, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao inserir funcionário: %s\n", PQerrorMessage(conn));
    } else {
        printf("Funcionário inserido com sucesso!\n");
    }

    PQclear(res);
}

void remover_funcionario(PGconn* conn) {
    char idFuncionario[10];

    printf("\n--- Remover Funcionário ---\n");
    printf("Digite o ID do funcionário a ser removido: ");
    fgets(idFuncionario, sizeof(idFuncionario), stdin);
    idFuncionario[strcspn(idFuncionario, "\n")] = 0;

    const char *query = "DELETE FROM Funcionarios WHERE idFuncionario = $1";
    
    const char *paramValues[1];
    paramValues[0] = idFuncionario;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao remover funcionário: %s\n", PQerrorMessage(conn));
    } else {
        if (atoi(PQcmdTuples(res)) == 0) {
            printf("Nenhum funcionário encontrado com o ID %s.\n", idFuncionario);
        } else {
            printf("Funcionário com ID %s removido com sucesso!\n", idFuncionario);
        }
    }

    PQclear(res);
}
