// Arquivo: cliente.h
#ifndef CLIENTE_H
#define CLIENTE_H

#include <libpq-fe.h> // Precisamos disto para usar PGconn

// Declaração da função que irá listar todos os clientes
void listar_clientes(PGconn* conn);

#endif // CLIENTE_H