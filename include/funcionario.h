#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <libpq-fe.h>

void listar_funcionarios(PGconn* conn);
void inserir_funcionario(PGconn* conn);
void remover_funcionario(PGconn* conn);

#endif