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
				break;
				
			case 'C':
				break;
				
			case 'D':
				break;
				
			case 'E':
				break;
		}
	}while(opcaoDesejada != 'Z');
}
