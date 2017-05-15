/*
	Sintese:
		Objetivo: Elaborar um programa para auxiliar no controle das
		atividades realizadas pelos frequentadores de uma rede de academias.
	
		Entrada: Dados dos frequentadores, series e atividades das academias
		
		Saida: Varias pesquisas
*/

#include "funcoes.h"
#include "estruturas.h"

int main(){
	
	char opcao;
	

	do{
		LIMPA_TELA;
	
		printf("Frequentador\n");
		printf(" A - Cadastrar novo\n");
		printf(" B - Alterar dados\n");
		printf(" C - Excluir\n\n");
	
		printf("Serie de exercicios\n");
		printf(" D - Cadastrar nova\n");
		printf(" E - Alterar dados\n");
		printf(" F - Excluir\n\n");
	
		printf("Atividades desenvolvidas\n");
		printf(" G - Incluir nova\n");
		printf(" H - Excluir\n\n");
	
		printf(" Z - Encerrar programa\n\n");
	
		printf("Opcao -> ");
	
		LIMPA_BUFFER;
		opcao = getchar();
	
		switch(opcao){
			case 'A':
				break;
			case 'B':
				break;
			case 'C':
				break;
			case 'D':
				break;
			case 'E':
				break;
			case 'F':
				break;
			case 'G':
				break;
			case 'H':
				break;
		
		}
	}while(opcao != 'Z');
	
	return 0;
}
