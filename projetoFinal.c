// Aluno : Gustavo Henrique de Oliveira Santos
// Matricula: UC16200774
// Aluno : Isnard de Sousa Silva
// Matricula: UC16200677

/*
	Sintese:
		Objetivo: Elaborar um programa para auxiliar no controle das
		atividades realizadas pelos frequentadores de uma rede de academias.
	
		Entrada: Dados dos frequentadores, series e atividades das academias
		
		Saida: Varias pesquisas
*/

#include "definicoes.h"
#include "funcoesBasicas.h"
#include "academia.h"
#include "frequentador.h"
#include "series.h"
#include "atividades.h"
#include "relatorios.h"

int main(void){
	char opcaoDesejada;
	
	
	// Verificando se o arquivo com os dados da academia e valido/existe
	if(verifArqAcademiaValido() == 0){
		// Tentando cadastrar os dados da academia
		if(cadastraDadosAcademia() == 0){
			printf("Nao foi possivel identificar a academia! \nO programa sera encerrado.");
			return 0;
		}
	}
	
	// Exibindo o menu com as opcoes disponiveis
	do{
		LIMPA_TELA;
		apresentaDadosAcademia();
		apresentaOpcoesMenuPrincipal();
		opcaoDesejada = leValidaOpcao("\nOpcao desejada: ", "Opcao invalida... Digite novamente: ", "ABCDEFGHIZ");
		LIMPA_TELA;
		
		switch(opcaoDesejada){
			case 'A':
				cadastraFrequentador();
				break;
			
			case 'B':
				alteraDadosFrequentador();
				break;
				
			case 'C':
				excluiFrequentador();
				break;
				
			case 'D':
				cadastraSerieEx();
				break;
			
			case 'E':
				alteraDadosSerieEx();
				break;
				
			case 'F':
				excluiSerieEx();
				break;
				
			case 'G':
				cadastraAtivDesenvolvida();
				break;
				
			case 'H':
				excluiAtivDesenvolvida();
				break;
			
			case 'I':
				geraRelatorios();
				break;
			
			case 'Z':
				printf("Programa encerrado!\n");
				break;
		}
	}while(opcaoDesejada != 'Z');
	
	return 0;
}
