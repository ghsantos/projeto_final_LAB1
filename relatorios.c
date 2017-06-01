#include "relatorios.h"

/*
	Objetivo: Controlar a geracao dos relatorios disponiveis pelo programa
	Parametros: nenhum
	Retorno: nenhum
*/
void geraRelatorios(void){
	char opcaoDesejada;
	
	do{
		LIMPA_TELA;
		apresentaDadosAcademia();
		apresentaOpcoesMenuRelatorios();
		opcaoDesejada = leValidaOpcao("Opcao desejada: ", "Opcao invalida... Digite novamente: ", "ABCDEZ");
		LIMPA_TELA;
		
		switch(opcaoDesejada){
			case 'A':
				break;
				
			case 'B':
				apresentaTodosCadastros();
				break;
				
			case 'C':
				pesqFrequentadoresPeloNome();
				break;
				
			case 'D':
				break;
				
			case 'E':
				break;
		}
	}while(opcaoDesejada != 'Z');
}

/*
	Objetivo: Controlar a exibicao de todos os frequentadores, series e atividades cadastradas
		no sistema
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaTodosCadastros(void){
	char opcaoDesejada;
	
	apresentaDadosAcademia();
	printf("\nDeseja ver todos os cadastros de: \n");
	printf("F - Frequentadores\n");
	printf("S - Series de exercicios\n");
	printf("A - Atividades desenvolvidas\n");
	printf("Z - Retornar a tela anterior\n\n");
	opcaoDesejada = leValidaOpcao("Opcao desejada: ", "Opcao invalida... Digite novamente: ", "FSAZ");
	LIMPA_TELA;
	
	switch(opcaoDesejada){
		case 'F':{
			apresentaDadosAcademia();
			printf("\n");
			apresentaDadosFrequentadoresArq();
			break;
		}
		
		case 'S':{
			apresentaDadosAcademia();
			printf("\n");
			apresentaDadosSeriesExsArq();
			break;
		}
		
		case 'Z':{
			return;
			break;
		}
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}
