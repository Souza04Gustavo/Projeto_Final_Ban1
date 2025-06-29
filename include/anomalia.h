#ifndef ANOMALIA_H
#define ANOMALIA_H

#include <libpq-fe.h>

// Função para listar todas as anomalias
void listar_anomalias(PGconn* conn);

#endif // ANOMALIA_H