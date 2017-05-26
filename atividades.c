#include "atividades.h"

/*
	Objetivo: Verificar se um frequentador ja fez uma atividade hoje
	Parametros: a struct da atividade desenvolvida
	Retorno: 1 se o frequentador fez, 0 caso contrario
*/
int fezAtividadeHoje(AtividadeDesenvolvida atividade){
	FILE *arqv;
	int fezAtividade=0;
	AtividadeDesenvolvida ativddAux;
	
	arqv = fopen(NOME_ARQ_ATIVDESEV, "rb");
	
	if(arqv != NULL){
	
		while(!feof(arqv)){
			if(fread(&ativddAux, sizeof(AtividadeDesenvolvida), 1, arqv) == 1){
				if(atividade.matriculaFrequentador == ativddAux.matriculaFrequentador
				   && atividade.identificadorSerie == ativddAux.identificadorSerie){
					if(diferencaDias(atividade.dataInicio, ativddAux.dataInicio) == 0){
						fezAtividade = 1;
						break;
					}
				}
			} else{
				break;
			}
		}
	
		fclose(arqv);	
	}
	
	return fezAtividade;
}

/*
	Objetivo: Gravar os dados de uma atividade desenvolvida
	Parametros: a struct da atividade desenvolvida
	Retorno: 1 se os dados foram gravados corretamente, 0 caso contrario
*/
int gravaAtividade(AtividadeDesenvolvida atividade){
	FILE *arqv;
	
	if(verificaArqExiste(NOME_ARQ_ATIVDESEV)){
		arqv = fopen(NOME_ARQ_ATIVDESEV, "ab+");
	} else{
		arqv = fopen(NOME_ARQ_ATIVDESEV, "wb+");
	}
	
	if(arqv == NULL){
		return 0;
	}
	
	if(fwrite(&atividade, sizeof(AtividadeDesenvolvida), 1, arqv) != 1){
		fclose(arqv);
		return 0;
	}
	
	fclose(arqv);

	return 1;
}

/*
	Objetivo: Cadastrar uma nova atividade a ser desenvolvida
	Parametros: nenhum
	Retorno: nenhum
*/
void cadastraAtividade(){
	AtividadeDesenvolvida atividade;
	
	if(!verificaArqExiste(NOME_ARQ_FREQ)){
		printf("Nenhum frequentador cadastrado\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}
	
	if(!verificaArqExiste(NOME_ARQ_SERIEEX)){
		printf("Nenhuma serie de exercicio cadatrada\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}

	apresentaDadosFrequentadores();
	
	atividade.matriculaFrequentador = leValidaInt("\nMatricula: ", "\nMatricula invalida\nTente novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
	
	if(obtemPosicaoFreqArq(atividade.matriculaFrequentador) == 0){
		printf("Matricula nao encontrada\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}
	
	LIMPA_TELA;
	
	listaSerieExercicios();
	
	atividade.identificadorSerie = leValidaInt("\nIdentificador da serie: ", "\nIdentificador invalido\nTente novamente: ", VAL_MIM_ID_SERIE, VAL_MAX_ID_SERIE);
	
	if(!existeSerie(atividade.identificadorSerie)){
		printf("Serie nao encontrada\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}
	
	atividade.dataInicio = obtemDataSistema();
	atividade.horarioInicio = obtemHoraSistema();
	
	if(fezAtividadeHoje(atividade)){
		printf("O frequentador ja realizou esta serie hoje\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}
	
	if(gravaAtividade(atividade)){
		printf("Atividade cadastrada com sucesso\n");
	} else {
		printf("Erro ao tentar cadastrar atividade\n");
	}
	
	continuarComEnter("\nPressione [Enter] para continuar...\n");
}

/*
	Objetivo: Excluir dados de uma atividade desenvolvida
	Parametros: nenhum
	Retorno: nenhum
*/
void excluiAtividade(){

}
