#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct Data{
	int dia;
	int mes;
	int ano;
} Data;

typedef struct Horario{
	int hora;
	int minuto;
} Horario;

typedef struct Frequentador{
	int matricula;
	char *nome;
	char *cpf;
	char sexo;
	struct Data dataIngresso;
} Frequentador;

typedef struct SerieExercicio{
	int identificadorSerie;
	char *descricao;
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
