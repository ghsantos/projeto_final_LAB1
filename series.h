#ifndef SERIES_H
#define SERIES_H

#include "academia.h"
#include "definicoes.h"
#include "funcoesBasicas.h"
#include "estruturas.h"

int obtemQtdSeriesCadastradas(void);
int obtemPosicaoSerieArq(int identificadorSeriePesq);
int obtemDadosSerieEx(SerieExercicio *serieExercicio, int posicaoSerieArq);
void apresentaDadosSeriesExs(void);
void apresentaDadosSerieEx(SerieExercicio *serieExercicio);

void cadastraSerieEx(void);
int existeSerie(int identificadorSerie);
int gravaDadosSerieNova(SerieExercicio *serieExercicio);

void alteraDadosSerieEx(void);
int modificaSerieEx(SerieExercicio *serieExercicio);
int gravaDadosSerieAlterada(SerieExercicio *serieExercicio, int posicaoSerieArq);

void excluiSerieEx(void);
int verifSerieJaFoiExecutada(int identificadorSeriePesq);
int removeDadosSerieArq(int identificadorSerieExc);

#endif	// SERIES_H
