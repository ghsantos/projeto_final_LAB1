// Diretivas de compilacao condicional
#ifndef ACADEMIA_H
#define ACADEMIA_H

#include "definicoes.h"
#include "estruturas.h"
#include "funcoesBasicas.h"

int verifArqAcademiaValido(void);
void apresentaDadosAcademia(void);
int cadastraDadosAcademia(void);
int gravaArqDadosAcademia(Academia *academia);

#endif // ACADEMIA_H
