#ifndef ESCALA_H
#define ESCALA_H

#include <libpq-fe.h>

// Função para listar todas as escalas
void listar_escalas(PGconn* conn);

#endif // ESCALA_H