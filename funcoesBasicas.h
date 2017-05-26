#ifndef FUNCOES_BASICAS_H
#define FUNCOES_BASICAS_H

#include "estruturas.h"

int leValidaInt(char *msg, char *msgErro, int valMin, int valMax);
float leValidaFloat(char *msg, char *msgErro, float valMin, float valMax);
void leValidaTexto(char *msg, char *msgErro, char *texto, int tamMinTexto, int tamMaxTexto);
void tiraTerminador(char *texto);
char leValidaOpcao(char *msg, char *msgErro, char *opcoesValidas);
int verifCPFValido(char *cpf);
void toLowerStr(char *str);
void toUpperStr(char *str);
int geraNroIntAleatorio(int valMin, int valMax);
Data obtemDataSistema(void);
Horario obtemHoraSistema(void);
int diferencaDias(Data dataInicial, Data dataFinal);
int verificaArqExiste(char *nomeArq);
void continuarComEnter(char *msg);
void apresentaOpcoesMenu(void);

#endif // FUNCOES_BASICAS_H
