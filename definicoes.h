#ifndef DEFINICOES_H
#define DEFINICOES_H

// Se for executado no S.O Linux
#ifdef __linux__
#include <stdio_ext.h>

#define LIMPA_TELA printf("\e[H\e[2J")
#define LIMPA_BUFFER  __fpurge(stdin)

// Senao
#else
#include <stdio.h>

#define LIMPA_TELA system("cls")
#define LIMPA_BUFFER fflush(stdin)
#endif // Fim da verificacao do S.O


// Diretivas
#define VAL_MIN_MATRIC_FREQ 1
#define VAL_MAX_MATRIC_FREQ 50000
#define VAL_MIN_IDSERIE 1
#define VAL_MAX_IDSERIE 1000
#define VAL_MIN_PESO 1
#define VAL_MAX_PESO 300
#define TAM_MIN_NOME_ACADEMIA 3
#define TAM_MAX_NOME_ACADEMIA 50
#define TAM_MIN_END_ACADEMIA 3
#define TAM_MAX_END_ACADEMIA 150
#define TAM_MIN_NOME_FREQ 3
#define TAM_MAX_NOME_FREQ 50
#define TAM_CPF 12
#define TAM_DESCRICAO_SERIE 150
#define TAM_MIN_DESCRICAO_SERIE 8
#define NOME_ARQ_ACAD "dadosAcademia.bin"
#define NOME_ARQ_FREQ "dadosFrequentadores.bin"
#define NOME_ARQ_SERIEEX "dadosSerieExercicios.bin"
#define NOME_ARQ_ATIVDESEV "dadosAtivDesenvolvidas.bin"

#define VAL_MAX_ID_SERIE 50000
#define VAL_MIM_ID_SERIE 1
#define VAL_MAX_DURACAO_SERIE 200
#define VAL_MIM_DURACAO_SERIE 5
#define VAL_MAX_CAL_PERDIDAS 20000
#define VAL_MIM_CAL_PERDIDAS 100

// Includes
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#endif // DEFINICOES_H
