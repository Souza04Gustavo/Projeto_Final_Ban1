#include <stdio.h>
#include <stdlib.h>
#include "relatorios.h"

// --- CONSULTA COM JUNÇÃO (JOIN) ---
// Ideia de Consulta: "Listar o nome de cada cliente e o modelo do equipamento que ele está usando."
void relatorio_clientes_equipamentos(PGconn* conn) {
    // A query SQL com INNER JOIN
    const char *query =
        "SELECT c.nome, e.modelo "
        "FROM Clientes AS c "
        "INNER JOIN Equipamento AS e ON c.idEquipamento_ativo = e.idEquipamento "
        "ORDER BY c.nome;";

    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao executar relatório de clientes e equipamentos: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int num_rows = PQntuples(res);
    printf("\n--- Relatório: Clientes e Seus Equipamentos Ativos (%d encontrados) ---\n", num_rows);
    printf("+--------------------------------+---------------------------+\n");
    printf("| %-30s | %-25s |\n", "Nome do Cliente", "Modelo do Equipamento");
    printf("+--------------------------------+---------------------------+\n");

    if (num_rows == 0) {
        printf("| Nenhum cliente com equipamento ativo encontrado.                              |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("| %-30s | %-25s |\n",
                   PQgetvalue(res, i, 0), // c.nome
                   PQgetvalue(res, i, 1)  // e.modelo
            );
        }
    }
    printf("+--------------------------------+---------------------------+\n");

    PQclear(res);
}

// --- CONSULTA COM SUBQUERY E AGREGAÇÃO ---
// Ideia de Consulta: "Para cada cliente, contar quantas anomalias foram registradas em seus equipamentos."
void relatorio_anomalias_por_cliente(PGconn* conn) {
    // Para cada cliente (c), executamos uma subquery.
    // A subquery conta (*) todas as anomalias (a) onde o id do equipamento da anomalia
    // é o mesmo que o id do equipamento ativo do cliente.
    const char *query =
        "SELECT c.nome, "
        "  (SELECT COUNT(*) FROM Anomalias AS a WHERE a.idEquipamento = c.idEquipamento_ativo) AS total_anomalias "
        "FROM Clientes AS c "
        "ORDER BY total_anomalias DESC, c.nome;";

    PGresult* res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Erro ao executar relatório de anomalias por cliente: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }

    int num_rows = PQntuples(res);
    printf("\n--- Relatório: Total de Anomalias por Cliente (%d clientes listados) ---\n", num_rows);
    printf("+--------------------------------+----------------------+\n");
    printf("| %-30s | %-20s |\n", "Nome do Cliente", "Total de Anomalias");
    printf("+--------------------------------+----------------------+\n");

    if (num_rows == 0) {
        printf("| Nenhum cliente encontrado.                                   |\n");
    } else {
        for (int i = 0; i < num_rows; i++) {
            printf("| %-30s | %-20s |\n",
                   PQgetvalue(res, i, 0), // c.nome
                   PQgetvalue(res, i, 1)  // total_anomalias (resultado do COUNT)
            );
        }
    }
    printf("+--------------------------------+----------------------+\n");

    PQclear(res);
}