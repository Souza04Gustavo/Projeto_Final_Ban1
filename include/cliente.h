// Arquivo: cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

#include <libpq-fe.h>

void listar_clientes(PGconn* conn);
void inserir_cliente(PGconn* conn);
void remover_cliente(PGconn* conn);



#endif // CLIENTE_H