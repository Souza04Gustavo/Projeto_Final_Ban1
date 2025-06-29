// Arquivo: database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <libpq-fe.h> // Inclui a biblioteca do PostgreSQL

// Função para estabelecer uma conexão com o banco de dados.
// Retorna um ponteiro para a estrutura de conexão (PGconn) ou NULL em caso de erro.
PGconn* conectar_bd();


// Função para fechar a conexão com o banco de dados.
void desconectar_bd(PGconn* conn);


#endif // DATABASE_H