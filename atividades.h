#ifndef ATIVIDADES_H
#define ATIVIDADES_H

#include "definicoes.h"
#include "estruturas.h"
#include "funcoesBasicas.h"
#include "frequentador.h"
#include "series.h"

void apresentaDadosAtivsDesenvolvidas(void);
void apresentaDadosAtivDesenvolvida(AtividadeDesenvolvida *ativDesenvolvida);
int obtemQtdAtivDesevCadastradas(void);
int fezAtividadeHoje(AtividadeDesenvolvida atividade);
int obtemPosicaoAtivDesenvArq(int matricFreqPesq, int idSerieExPesq);
int obtemDadosAtivDesenvolvida(AtividadeDesenvolvida *ativDesenvolvida, int posicaAtivDesevArq);

void cadastraAtivDesenvolvida(void);
int gravaDadosAtivDesenvolvidaArq(AtividadeDesenvolvida *ativDesenvolvida);

void excluiAtivDesenvolvida(void);
int removeDadosAtivDesevArq(int matricFreqPesq, int idSerieExPesq);

#endif	// ATIVIDADES
