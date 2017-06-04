// Diretivas de compilacao condicional
#ifndef FUNCOES_BASICAS_H
#define FUNCOES_BASICAS_H

#include "definicoes.h"
#include "estruturas.h"

int leValidaInt(char *msg, char *msgErro, int valMin, int valMax);
float leValidaFloat(char *msg, char *msgErro, float valMin, float valMax);
void leValidaTexto(char *msg, char *msgErro, char *texto, int tamTexto);
void tiraTerminador(char *texto);
char leValidaOpcao(char *msg, char *msgErro, char *opcoesValidas);
Data leValidaData(char *msg);

int verifCPFValido(char *cpf);
int verifDataValida(Data dataVerif);

void toLowerStr(char *str);
void toUpperStr(char *str);

int geraNroIntAleatorio(int valMin, int valMax);
Data obtemDataSistema(void);
Horario obtemHoraSistema(void);
int diferencaDias(Data dataInicial, Data dataFinal);
int verificaIntervaloDatas(Data dataInicial, Data dataFinal, Data dataIntervalo);
int verificaArqExiste(char *nomeArq);
void continuarComEnter(char *msg);

void apresentaOpcoesMenuPrincipal(void);
void apresentaOpcoesMenuRelatorios(void);

#endif // FUNCOES_BASICAS_H
