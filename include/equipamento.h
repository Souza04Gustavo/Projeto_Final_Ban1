#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include <libpq-fe.h>

void listar_equipamentos(PGconn* conn);
void inserir_equipamento(PGconn* conn);
void remover_equipamento(PGconn* conn);

#endif // EQUIPAMENTO_H