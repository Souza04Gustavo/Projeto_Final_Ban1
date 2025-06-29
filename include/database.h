#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h> // Inclui a biblioteca do PostgreSQL

// Função para estabelecer uma conexão com o banco de dados.
PGconn* conectar_bd();


void desconectar_bd(PGconn* conn);


#endif // DATABASE_H