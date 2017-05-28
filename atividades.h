#ifndef ATIVIDADES_H
#define ATIVIDADES_H

#include "definicoes.h"
#include "estruturas.h"
#include "funcoesBasicas.h"
#include "frequentador.h"
#include "series.h"


int fezAtividadeHoje(AtividadeDesenvolvida atividade);

int gravaAtividade(AtividadeDesenvolvida atividade);

void cadastraAtividade();

void printAtivddDesenv(AtividadeDesenvolvida atividade, int modo);

void listaAtividades();

int obtemQtdAtivCadastradas();

int existeAividade(int identificadorSerie, int matriculaFrequentador);

AtividadeDesenvolvida obtemAtividade(int identificadorSerie, int matriculaFrequentador);

void excluiAtividade();

int removeAtvddDesenvlvida(AtividadeDesenvolvida atividade);

#endif	// ATIVIDADES
