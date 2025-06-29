#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include <libpq-fe.h>

// Função para listar todos os equipamentos
void listar_equipamentos(PGconn* conn);

#endif // EQUIPAMENTO_H