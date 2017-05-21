// Aluno : 

/*
 Sintese
   Objetivo:
 
   Entrada : 

   Saida   :  

*/

#include "definicoes.h"
#include "funcoesBasicas.h"
#include "academia.h"

int main(void){
	char opcaoDesejada;
	
	
	// Verificando se o arquivo com os dados da academia e valido/existe
	if(verifArqAcademiaValido() == 0){
		// Tentando cadastrar os dados da academia
		if(cadastraAcademia() == 0){
			printf("Nao foi possivel identificar a academia! \nO programa sera encerrado.");
			return 0;
		}
	}
	
	// Exibindo o menu com as opcoes disponiveis
	do{
		LIMPA_TELA;
		apresentaDadosAcademia();
		apresentaOpcoesMenu();
		opcaoDesejada = leValidaOpcao("\nOpcao desejada: ", "Opcao invalida... Digite novamente: ", "ABCDEFGHZ");
		
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
				
			case 'F':
				break;
				
			case 'G':
				break;
				
			case 'H':
				break;
				
			case 'Z':
				printf("\n\nPrograma encerrado!");
				break;
		}
	}while(opcaoDesejada != 'Z');
	
	return 0;
}
