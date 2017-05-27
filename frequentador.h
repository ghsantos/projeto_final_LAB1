#ifndef FREQUENTADOR_H
#define FREQUENTADOR_H

#include "definicoes.h"
#include "estruturas.h"
#include "funcoesBasicas.h"
#include "academia.h"

int obtemQtdFreqCadastrados(void);
int obtemPosicaoFreqArq(int matriculaPesq);
int obtemDadosFrequentador(Frequentador *frequentador, int posicaoFreqArq);
void apresentaDadosFrequentadores(void);
void apresentaDadosFrequentador(Frequentador *frequentador);

void cadastraFrequentador(void);
int gravaDadosFreqNovo(Frequentador *frequentador);

void alteraDadosFrequentador(void);
int modificaFrequentador(Frequentador *frequentador);
int gravaDadosFreqAlterado(Frequentador *frequentador, int posicaoFreqArq);

void excluiFrequentador(void);
int verifFreqDevAtividades(int matriculaVerif);
int removeDadosFreqArq(int matriculaFreqExc);

#endif // FREQUENTADOR_H
