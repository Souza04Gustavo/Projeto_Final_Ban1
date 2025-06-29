#ifndef ANOMALIA_H
#define ANOMALIA_H

#include <libpq-fe.h>

void listar_anomalias(PGconn* conn);
void inserir_anomalia(PGconn* conn);
void remover_anomalia(PGconn* conn);

#endif // ANOMALIA_H