#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "definicoes.h"

typedef struct Data{
	int dia;
	int mes;
	int ano;
} Data;

typedef struct Horario{
	int hora;
	int minutos;
} Horario;

typedef struct Academia{
	char nome[TAM_MAX_NOME_ACADEMIA];
	char endereco[TAM_MAX_END_ACADEMIA];
} Academia;

typedef struct Frequentador{
	int matricula;
	char nome[TAM_MAX_NOME_FREQ];
	char cpf[TAM_CPF];
	float peso;
	char sexo;
	struct Data dataIngresso;
} Frequentador;

typedef struct SerieExercicio{
	int identificadorSerie;
	char descricao[TAM_DESCRICAO_SERIE];
	int duracao;
	int qtdCaloriasPerdidas;
} SerieExercicio;

typedef struct AtividadeDesenvolvida{
	int matriculaFrequentador;
	int identificadorSerie;
	struct Data dataInicio;
	struct Horario horarioInicio;
} AtividadeDesenvolvida;

#endif // ESTRUTURAS_H
