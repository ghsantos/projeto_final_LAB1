#ifndef SERIES_H
#define SERIES_H

#include "definicoes.h"
#include "funcoesBasicas.h"
#include "estruturas.h"


int existeSerie(int identificadorSerie);

SerieExercicio obtemSerie(int identificadorSerie);

void printSerieExercicio(SerieExercicio serie, int modo);

void listaSerieExercicios();

int leSerieExercicios(SerieExercicio *serie, int modo);

void cadastraNovaSerie();

void alteraDadosSeries();

void excluirSeries();

#endif	// SERIES_H
