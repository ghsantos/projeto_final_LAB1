#ifndef FUNC_LAB_H
#define FUNC_LAB_H

#ifdef __linux__
#include <stdio_ext.h>

#define LIMPA_TELA printf("\e[H\e[2J")
#define LIMPA_BUFFER  __fpurge(stdin)

#else
#include <stdio.h>

#define LIMPA_TELA system("cls")
#define LIMPA_BUFFER fflush(stdin)
#endif

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


#define MAX_MATRICULA 50000

/*
    Objetivo: ler e alocar dinamicamente uma string
    Parâmetros: nenhum
    retorno: o endereco de memoria da string alocada
*/
char * leAlocaStr(){

	char *str;
	char aux;
	int cont=0;
	
	str = (char *) malloc(sizeof(char));
	
	LIMPA_BUFFER;
	
	do{
		aux = getchar();
		
		if(aux != '\n'){
			str[cont] = aux;
			
			str = (char *) realloc(str, sizeof(char) * (cont + 2));
		} else{
			str[cont] = '\0';
		}
	
		++cont;
	}while(aux != '\n');

	LIMPA_BUFFER;

	return str;
}

/*
    Objetivo: ler corretamente uma string
    Parâmetros: Uma referencia para uma string e o tamanho dela
    retorno: nenhum
*/
int leValidaString(char *str, int max, int min){

	int leituraValida = 1;

	LIMPA_BUFFER;
	fgets(str, max, stdin);

	if(str[strlen(str) - 1] == '\n'){
		str[strlen(str) - 1] = '\0';
	}
	
	if(strlen(str) < min || strlen(str) > max){
		leituraValida = 0;
	}
	
	return leituraValida;
}

/*
	Objetivo: ler e validar um numero float
	Parâmetros: nenhum
	retorno: o numero float validado
*/
float leValidaFloat(){

	float num;

	LIMPA_BUFFER;

	while(scanf("%f", &num) != 1){
		LIMPA_BUFFER;
		printf("Tente novamente: ");
	}

	return num;
}

/*
	Objetivo: ler e validar continuar ou nao
	Parâmetros: nenhum
	retorno: S ou N
*/
char leValidaSN(){

	char simNao;

	do{
		LIMPA_BUFFER;
		simNao = getchar();

		simNao = toupper(simNao);

		if(simNao != 'N' && simNao != 'S'){
			printf("Opcao invalida\n");
			printf("Tente novamente: ");
		}
	}while(simNao != 'N' && simNao != 'S');

	printf("\n");

	return simNao;
}

/*
	Objetivo: ler e validar o sexo
	Parâmetros: nenhum
	retorno: M ou F
*/
char leValidaSexo(){

	char sexo;

	printf("Sexo: ");

	do{
		LIMPA_BUFFER;
		sexo = getchar();

		sexo = toupper(sexo);

		if(sexo != 'M' && sexo != 'F'){
			printf("Sexo invalido\n");
			printf("Tente novamente: ");
		}
	}while(sexo != 'M' && sexo != 'F');

	return sexo;
}

/*
	Objetivo: ler e validar um numero int
	Parâmetros: nenhum
	retorno: o numero int validado
*/
int leValidaInt(){

	int num;

	LIMPA_BUFFER;

	while(scanf("%d", &num) != 1){
		LIMPA_BUFFER;
		printf("Tente novamente: ");
	}

	return num;
}

/*
	Objetivo: verificar a existenica de uma substring em uma string ignorando case
	Parâmetros: uma string e uma substring
 	retorno: se a substring existe na string ou nao
*/
int strcasestrLAB(const char *texto, const char *pesqsa){
	int existe=0, cont;

	char *str, *find;
	
	str = (char *) malloc(sizeof(char) * strlen(texto));
	
	find = (char *) malloc(sizeof(char) * strlen(pesqsa));

	for(cont=0; cont < strlen(texto); ++cont){
		str[cont] = toupper(texto[cont]);
	}

	str[cont] = '\0';

	for(cont=0; cont < strlen(pesqsa); ++cont){
		find[cont] = toupper(pesqsa[cont]);
	}

	find[cont] = '\0';

	if(strstr(str, find) != NULL){
		existe = 1;
	}
	
	free(str);
	free(find);

	return existe;
}

/*
	Objetivo: converter os caracteres de uma string para minusculo
	Parâmetros: referencia para uma string
	retorno: nenhum
*/
void tolowerStr(char *str){
	int cont;

	for(cont = 0; cont < strlen(str); ++cont){
		str[cont] = tolower(str[cont]);
	}
}

/*
	Objetivo: converter os caracteres de uma string para maiusculo
	Parâmetros: referencia para uma string
	retorno: nenhum
*/
void toupperStr(char *str){
	int cont;

	for(cont = 0; cont < strlen(str); ++cont){
		str[cont] = tolower(str[cont]);
	}
}

/*
	Objetivo: Gerar um numero aleatorio menor que MAX_MATRICULA
	Parâmetros: nenhum
	retorno: o numero aleatorio
*/
int geraNumAle(){
	int num;
	
	srand((unsigned)time(NULL));
	
	num = rand() % MAX_MATRICULA;
	
	return num;
}

#endif // #define FUNC_LAB_H
