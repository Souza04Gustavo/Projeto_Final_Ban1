#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <libpq-fe.h>

void listar_funcionarios(PGconn* conn);

#endif