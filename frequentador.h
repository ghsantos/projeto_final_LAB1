#ifndef FREQUENTADOR_H
#define FREQUENTADOR_H

void cadastraFrequentador(void);
int obtemPosicaoFreqArq(int matriculaPesq);
int gravaDadosFreqArq(Frequentador *frequentador);
void apresentaDadosFrequentadores(void);
void alteraDadosFrequentador(void);
int obtemDadosFrequentadorArq(Frequentador *frequentador, int posicaoFreqArq);
void apresentaDadosFrequentador(Frequentador *frequentador);
int gravaDadosFreqAlterados(Frequentador *frequentador, int posicaoFreqArq);
void excluiFrequentador(void);
int removeFreqArq(int matriculaFreqExc);
int verifFreqDevAtividades(int matriculaVerif);

#endif // FREQUENTADOR_H
