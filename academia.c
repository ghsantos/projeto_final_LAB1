#include "definicoes.h"
#include "estruturas.h"
#include "funcoesBasicas.h"
#include "academia.h"

/*
	Objetivo: Verificar se o arquivo com os dados da academia e valido
	Parametros: endereco de memoria da string com o nome do arquivo
	Retorno: 0(invalido) ou 1(valido)
*/
int verifArqAcademiaValido(void){
	Academia academia;
	FILE *arq;
	int arqValido=0;
	
	arq = fopen(NOME_ARQ_ACAD, "rb");
	if(arq != NULL){
		while(feof(arq) == 0){
			if(fread(&academia, sizeof(Academia), 1, arq) == 1){
				arqValido=1;
			}
		}
		fclose(arq);
	}
	
	return arqValido;
}

/*
	Objetivo: Apresentar o nome e o endereco da academia formatados em uma linha
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaDadosAcademia(void){
	Academia academia;
	FILE *arq;
	int dadosEncontrados=0;
	
	arq = fopen(NOME_ARQ_ACAD, "rb");
	if(arq != NULL){
		if(fread(&academia, sizeof(Academia), 1, arq) == 1){
			dadosEncontrados=1;
		}
		fclose(arq);
	}
	
	if(dadosEncontrados == 0){
		printf("OS DADOS DA ACADEMIA NAO FORAM LOCALIZADOS\n");
	} else {
		printf("%s - %s\n", academia.nome, academia.endereco);
	}
}

/*
	Objetivo: Cadastrar os dados da academia
	Parametros: nenhum
	Retorno: 0(erro na gravacao) ou 1(gravacao concluida com exito)
*/
int cadastraAcademia(void){
	Academia academia;
	int cadastroConcluido=0;
	
	printf("DADOS DA ACADEMIA\n\n");
	leValidaTexto("Nome: ", "Nome invalido... Digite novamente: ", academia.nome, TAM_MIN_NOME_ACADEMIA, TAM_MAX_NOME_ACADEMIA);
	leValidaTexto("\nEndereco: ", "Endereco invalido... Digite novamente: ", academia.endereco, TAM_MIN_END_ACADEMIA, TAM_MAX_END_ACADEMIA);
	
	// Tentando gravar os dados da academia em um arquivo de saida
	if(gravaArqDadosAcademia(&academia) == 1){
		printf("\n\nDados gravados com sucesso!");
		printf("\n\nPressione 'Enter' para continuar...");
		getchar();
		cadastroConcluido=1;
	}
	
	return cadastroConcluido;
}

/*
	Objetivo: Gravar os dados da academia em um arquivo de saida
	Parametros: endereco de memoria da struct com os dados da academia
	Retorno: 0(erro na gravacao) ou 1(gravacao concluida com exito)
*/
int gravaArqDadosAcademia(Academia *academia){
	FILE *arq;
	int gravacaoConcluida;
	
	arq = fopen(NOME_ARQ_ACAD, "wb");
	if(arq != NULL){
		if(fwrite(academia, sizeof(Academia), 1, arq) == 1){
			gravacaoConcluida=1;
		}
		fclose(arq);
	}
	
	return gravacaoConcluida;
}
