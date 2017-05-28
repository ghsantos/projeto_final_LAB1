#ifndef SERIES_H
#define SERIES_H

#include "academia.h"
#include "definicoes.h"
#include "funcoesBasicas.h"
#include "estruturas.h"


int existeSerie(int identificadorSerie);

SerieExercicio obtemSerie(int identificadorSerie);

void printSerieExercicio(SerieExercicio serie, int modo);

void listaSerieExercicios();

int leSerieExercicios(SerieExercicio *serie, int modo);

void cadastraNovaSerie();

int obtemQtdSeriesCadastradas();

void alteraDadosSeries();

void excluirSeries();

#endif	// SERIES_H
