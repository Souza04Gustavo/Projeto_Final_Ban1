#ifndef EQUIPE_H
#define EQUIPE_H

#include <libpq-fe.h>

void listar_equipes(PGconn* conn);
void inserir_equipe(PGconn* conn);
void remover_equipe(PGconn* conn);

#endif // EQUIPE_H