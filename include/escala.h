#ifndef ESCALA_H
#define ESCALA_H

#include <libpq-fe.h>

void listar_escalas(PGconn* conn);
void inserir_escala(PGconn* conn);
void remover_escala(PGconn* conn);

#endif // ESCALA_H