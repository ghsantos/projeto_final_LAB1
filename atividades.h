#ifndef ATIVIDADES_H
#define ATIVIDADES_H

#include "definicoes.h"
#include "estruturas.h"
#include "funcoesBasicas.h"
#include "frequentador.h"
#include "series.h"

void apresentaDadosAtividadesArq(void);
void apresentaDadosAtividadesArqIndice(void);
void apresentaDadosAtivDesenvolvida(AtividadeDesenvolvida *ativDesenvolvida);
void apresentaAtivsFrequentador(int matriculaPesq);

int obtemPosicaoAtivDesenvArq(int matricFreqPesq, int idSerieExPesq);
int obtemQtdAtivDesevCadastradas(void);
int obtemDadosAtivPorChaveUnica(AtividadeDesenvolvida *ativDesenvPesq);
int obtemDadosAtivPorPosicaoArq(AtividadeDesenvolvida *ativDesenvolvida, int posicaAtivDesevArq);

int verifFreqFezAtividadeHoje(AtividadeDesenvolvida atividade);
int verifFreqFezAlgumaAtividade(int matriculaVerif);

void cadastraAtivDesenvolvida(void);
int gravaDadosAtivDesenvolvidaArq(AtividadeDesenvolvida *ativDesenvolvida);

void excluiAtivDesenvolvida(void);
int removeDadosAtivDesevArq(int indice);

void pesqAtivDesevPorChaveUnica(void);

#endif	// ATIVIDADES
