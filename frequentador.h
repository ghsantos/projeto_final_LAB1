#ifndef FREQUENTADOR_H
#define FREQUENTADOR_H

#include "definicoes.h"
#include "estruturas.h"
#include "funcoesBasicas.h"
#include "academia.h"
#include "series.h"
#include "atividades.h"

int obtemQtdFreqCadastrados(void);
int obtemPosicaoFreqArq(int matriculaPesq);
int obtemDadosFreqPorPosicaoArq(Frequentador *frequentador, int posicaoFreqArq);
int obtemDadosSeriePorPosicaoArq(SerieExercicio *serieExercicio, int posicaoSerieArq);
void apresentaDadosFrequentadoresArq(void);
void apresentaDadosFrequentadoresMemoria(Frequentador *frequentadores, int qtdFreq);
void apresentaDadosFrequentador(Frequentador *frequentador);

void cadastraFrequentador(void);
int gravaDadosFreqNovo(Frequentador *frequentador);

void alteraDadosFrequentador(void);
int modificaFrequentador(Frequentador *frequentador);
int gravaDadosFreqAlterado(Frequentador *frequentador, int posicaoFreqArq);

void excluiFrequentador(void);
int removeDadosFreqArq(int matriculaFreqExc);

void pesqFrequentadorPelaMatric(void);
void pesqFrequentadoresPeloNome(void);
void ordenaFreqPeloNome(Frequentador *frequentadores, int qtdFreq);
int verificaOrdenacaoNomeFreq(const void *p1, const void *p2);

#endif // FREQUENTADOR_H
