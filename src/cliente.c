#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

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
    
    printf("+-------+--------------------------------+-----------------+-----------------+--------------------------------+----------------------+---------------------+\n");
    printf("| %-5s | %-30s | %-15s | %-15s | %-30s | %-20s | %-19s |\n", "ID", "Nome", "Nascimento", "CPF", "Endereço", "Telefone", "ID Equip. Ativo");
    printf("+-------+--------------------------------+-----------------+-----------------+--------------------------------+----------------------+---------------------+\n");

    if (num_rows == 0) {
        printf("| Nenhum cliente cadastrado.                                                                                                                            |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
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


void inserir_cliente(PGconn* conn) {
    char nome[101];
    char dataNascimento[12]; // Formato AAAA-MM-DD
    char cpf[16];
    char endereco[256];
    char telefone[21];
    char idEquipamento[10];

    printf("\n--- Inserir Novo Cliente ---\n");

    printf("Nome completo: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Data de Nascimento (formato AAAA-MM-DD): ");
    fgets(dataNascimento, sizeof(dataNascimento), stdin);
    dataNascimento[strcspn(dataNascimento, "\n")] = 0;

    printf("CPF (formato XXX.XXX.XXX-XX): ");
    fgets(cpf, sizeof(cpf), stdin);
    cpf[strcspn(cpf, "\n")] = 0;

    printf("Endereço: ");
    fgets(endereco, sizeof(endereco), stdin);
    endereco[strcspn(endereco, "\n")] = 0;

    printf("Telefone: ");
    fgets(telefone, sizeof(telefone), stdin);
    telefone[strcspn(telefone, "\n")] = 0;

    printf("ID do Equipamento Ativo (deixe em branco se não houver): ");
    fgets(idEquipamento, sizeof(idEquipamento), stdin);
    idEquipamento[strcspn(idEquipamento, "\n")] = 0;
    
    const char *query = "INSERT INTO Clientes (nome, dataNascimento, cpf, endereco, telefone, idEquipamento_ativo) VALUES ($1, $2, $3, $4, $5, $6)";

    const char *paramValues[6];
    paramValues[0] = nome;
    paramValues[1] = dataNascimento;
    paramValues[2] = cpf;
    paramValues[3] = endereco;
    paramValues[4] = telefone;
    paramValues[5] = (strlen(idEquipamento) > 0) ? idEquipamento : NULL;

    PGresult* res = PQexecParams(conn, query, 6, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao inserir cliente: %s\n", PQerrorMessage(conn));
    } else {
        printf("Cliente inserido com sucesso!\n");
    }

    PQclear(res);
}

void remover_cliente(PGconn* conn) {
    char idCliente[10];

    printf("\n--- Remover Cliente ---\n");
    printf("Digite o ID do cliente a ser removido: ");
    fgets(idCliente, sizeof(idCliente), stdin);
    idCliente[strcspn(idCliente, "\n")] = 0;

    const char *query = "DELETE FROM Clientes WHERE idCliente = $1";
    
    const char *paramValues[1];
    paramValues[0] = idCliente;

    PGresult* res = PQexecParams(conn, query, 1, NULL, paramValues, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Erro ao remover cliente: %s\n", PQerrorMessage(conn));
    } else {
        if (atoi(PQcmdTuples(res)) == 0) {
            printf("Nenhum cliente encontrado com o ID %s.\n", idCliente);
        } else {
            printf("Cliente com ID %s removido com sucesso!\n", idCliente);
        }
    }

    PQclear(res);
}