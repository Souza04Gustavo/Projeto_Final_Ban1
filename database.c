// Arquivo: database.c
#include <stdio.h>
#include <stdlib.h>
#include "database.h" // Inclui nossa própria definição

PGconn* conectar_bd() {
    // --- IMPORTANTE: SUBSTITUA COM SEUS DADOS ---
    const char *conninfo = "dbname=postgres user=postgres password=password host=localhost";

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Erro de conexão com o banco de dados: %s\n", PQerrorMessage(conn));
        PQfinish(conn); // Libera a memória da tentativa de conexão
        return NULL;
    }

    printf("Conexão com o banco de dados estabelecida com sucesso!\n");
    return conn;
}

void desconectar_bd(PGconn* conn) {
    if (conn != NULL) {
        PQfinish(conn);
        printf("Conexão com o banco de dados fechada.\n");
    }
}