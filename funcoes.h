#ifndef FUNC_LAB_H
#define FUNC_LAB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    Objetivo: ler corretamente uma string
    Parâmetros: Uma referencia para uma string e o tamanho dela
    retorno: nenhum
*/
void leString(char *str, int tamanho){

	LIMPA_BUFFER;
	fgets(str, tamanho, stdin);

	if(str[strlen(str) - 1] == '\n'){
		str[strlen(str) - 1] = '\0';
	}
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

#endif // #define FUNC_LAB_H
