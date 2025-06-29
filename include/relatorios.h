#ifndef RELATORIOS_H
#define RELATORIOS_H

#include <libpq-fe.h>

// Consulta com JOIN
void relatorio_clientes_equipamentos(PGconn* conn);

// Consulta com SUBQUERY e AGREGAÇÃO
void relatorio_anomalias_por_cliente(PGconn* conn);

#endif // RELATORIOS_H