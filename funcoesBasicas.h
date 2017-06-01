#ifndef FUNCOES_BASICAS_H
#define FUNCOES_BASICAS_H

#include "definicoes.h"
#include "estruturas.h"

int leValidaInt(char *msg, char *msgErro, int valMin, int valMax);
float leValidaFloat(char *msg, char *msgErro, float valMin, float valMax);
char* leString(void);
void leValidaTexto(char *msg, char *msgErro, char *texto, int tamMinTexto, int tamMaxTexto);
void tiraTerminador(char *texto);
char leValidaOpcao(char *msg, char *msgErro, char *opcoesValidas);
int verifCPFValido(char *cpf);
int verifDataValida(Data dataVerif);
void toLowerStr(char *str);
void toUpperStr(char *str);
int strcasestrLAB(const char *texto, const char *pesqsa);
int strcasecmpLAB(const char *texto1, const char *texto2);
int geraNroIntAleatorio(int valMin, int valMax);
Data obtemDataSistema(void);
Horario obtemHoraSistema(void);
int diferencaDias(Data dataInicial, Data dataFinal);
int verificaArqExiste(char *nomeArq);
void continuarComEnter(char *msg);
void apresentaOpcoesMenuPrincipal(void);
void apresentaOpcoesMenuRelatorios(void);

#endif // FUNCOES_BASICAS_H
