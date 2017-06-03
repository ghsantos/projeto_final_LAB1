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
		opcaoDesejada = leValidaOpcao("Opcao desejada: ", "Opcao invalida... Digite novamente: ", "ABCDEFGZ");
		LIMPA_TELA;
		
		switch(opcaoDesejada){
			case 'A':
				pesqCadastrosChaveUnica();
				break;
				
			case 'B':
				apresentaTodosCadastros();
				break;
				
			case 'C':
				pesqFrequentadoresPeloNome();
				break;
				
			case 'D':
				pesqFrequentadoresPelaSerie();
				break;
				
			case 'E':
				break;
			
			case 'F':
				break;
				
			case 'G':
				break;
		}
	}while(opcaoDesejada != 'Z');
}

/*
	Objetivo: Controlar a pesquisa dos frequentadores, series e atividades cadastradas
		atraves da sua respectiva chave unica
	Parametros: nenhum
	Retorno: nenhum
*/
void pesqCadastrosChaveUnica(void){
	char opcaoDesejada;
	
	apresentaDadosAcademia();
	printf("\nDeseja pesquisar: \n");
	printf("F - Frequentadores\n");
	printf("S - Series de exercicios\n");
	printf("A - Atividades desenvolvidas\n");
	printf("Z - Retornar a tela anterior\n\n");
	opcaoDesejada = leValidaOpcao("Opcao desejada: ", "Opcao invalida... Digite novamente: ", "FSAZ");
	LIMPA_TELA;
	
	switch(opcaoDesejada){
		case 'F':{
			pesqFrequentadorPelaMatric();
			break;
		}
		
		case 'S':{
			pesqSerieExPorCodIdentif();
			break;
		}
		
		case 'A':{
			pesqAtivDesevPelaChaveUnica();
			break;
		}
		
		case 'Z':{
			return;
			break;
		}
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
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
			obtemQtdFreqCadastrados() == 0 ? 
						printf("\n\nNao existem frequentadores cadastrados!") :
						apresentaDadosFrequentadoresArq();
			
			break;
		}
		
		case 'S':{
			apresentaDadosAcademia();
			printf("\n");
			obtemQtdSeriesCadastradas() == 0 ? 
						printf("\n\nNao existem series de exercicios cadastradas!") :
						apresentaDadosSeriesExsArq();
			break;
		}
		
		case 'A':{
			apresentaDadosAcademia();
			printf("\n");
			obtemQtdAtivDesevCadastradas() == 0 ? 
						printf("\nNao existem atividade desenvolvidas cadastradas!") :
						apresentaDadosAtividadesArqIndice();
			break;
		}
		
		case 'Z':{
			return;
			break;
		}
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}
