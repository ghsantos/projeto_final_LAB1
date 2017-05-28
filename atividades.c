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
	Objetivo: exibir uma atividade desenvolvida e o cabecalho se o modo for 1
	Parametros: Uma struct de serie de atividades e o modo de exibicao
	Retorno: nenhum
*/
void printAtivddDesenv(AtividadeDesenvolvida atividade, int modo){
	if(modo == 1){
		printf(" Matricula | Id da Serie | dd/mm/aaaa | hh:mm\n");
	}

	printf(" %9d | %11d | %2.2d/%2.2d/%4.4d | %2.2d:%2.2d\n", atividade.matriculaFrequentador,
		   atividade.identificadorSerie, atividade.dataInicio.dia, atividade.dataInicio.mes,
		   atividade.dataInicio.ano, atividade.horarioInicio.hora, atividade.horarioInicio.minutos);
}

/*
	Objetivo: Listar as atividades salvas na memoria
	Parametros: nenhum
	Retorno: nenhum
*/
void listaAtividades(){
	FILE *arqv;
	AtividadeDesenvolvida atividade;
	int cont=0;

	arqv = fopen(NOME_ARQ_ATIVDESEV, "rb");
	
	if(arqv != NULL){
		
		printf("Atividades desenvolvidas\n");
	
		while(!feof(arqv)){
			if(fread(&atividade, sizeof(AtividadeDesenvolvida), 1, arqv) == 1){
				printAtivddDesenv(atividade, cont+1);
				
				++cont;
			}
		}
		fclose(arqv);
	}

}

/*
	Objetivo: obter a quantidade de atividades salvas na memoria
	Parametros: nenhum
	Retorno: quantidade de atividades salvas na memoria
*/
int obtemQtdAtivCadastradas(){
	FILE *arq;
	int qtdAtividades=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		if(fseek(arq, 0, SEEK_END) == 0){
			qtdAtividades = ftell(arq) / sizeof(AtividadeDesenvolvida);
		}
		fclose(arq);
	}
	
	return qtdAtividades;
}

/*
	Objetivo: Verificar se uma atividades esta salvas na memoria
	Parametros: o identificador da serie e a matricula do frequentador
	Retorno: 1 se a atividade existe na memoria, 0 caso contrario
*/
int existeAividade(int identificadorSerie, int matriculaFrequentador){
	int existe = 0;
	FILE *arqv;
	AtividadeDesenvolvida atividade;
	
	arqv = fopen(NOME_ARQ_ATIVDESEV, "rb");
	
	if(arqv != NULL){
		
		while(!feof(arqv)){
			if(fread(&atividade, sizeof(AtividadeDesenvolvida), 1, arqv) == 1){
				if(atividade.matriculaFrequentador == matriculaFrequentador &&
				   atividade.identificadorSerie == identificadorSerie){
					existe = 1;
					break;
				}
			}
		}

		fclose(arqv);
	}
	
	return existe;
}

/*
	Objetivo: Obter uma atividades salva na memoria
	Parametros: o identificador da serie e a matricula do frequentador
	Retorno: a struct da atividade obtida
*/
AtividadeDesenvolvida obtemAtividade(int identificadorSerie, int matriculaFrequentador){
	AtividadeDesenvolvida atividade;
	FILE *arqv;
	
	arqv = fopen(NOME_ARQ_ATIVDESEV, "rb");
	
	if(arqv != NULL){
		
		while(!feof(arqv)){
			if(fread(&atividade, sizeof(AtividadeDesenvolvida), 1, arqv) == 1){
				if(atividade.matriculaFrequentador == matriculaFrequentador &&
				   atividade.identificadorSerie == identificadorSerie){
					break;
				}
			}
		}

		fclose(arqv);
	}
	
	return atividade;
}

/*
	Objetivo: Excluir dados de uma atividade desenvolvida
	Parametros: nenhum
	Retorno: nenhum
*/
void excluiAtividade(){
	AtividadeDesenvolvida atividade;
	char continuar;
	int identificadorSerie, matriculaFrequentador;
	
	if(obtemQtdAtivCadastradas() == 0){
		printf("Nenhuma atividade de exercicio cadastrada\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}

	listaAtividades();

	matriculaFrequentador = leValidaInt("\n\nMatricula do frequentador da atividade a ser excluido: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);

	identificadorSerie = leValidaInt("\nIdentificador da serie da atividade a ser excluida: ", "\nIdentificador invalido\nTente novamente: ", VAL_MIM_ID_SERIE, VAL_MAX_ID_SERIE);

	if(!existeAividade(identificadorSerie, matriculaFrequentador)){
		printf("\nAtividade nao encontrada\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}

	LIMPA_TELA;
	
	atividade = obtemAtividade(identificadorSerie, matriculaFrequentador);

	printAtivddDesenv(atividade, 1);

	continuar = leValidaOpcao("\nConfirmar exclusao (S/n)? ", "Opcao invalida\nTente novamente: ", "SN");

	if(continuar == 'N'){
		return;
	}
	

	if(removeAtvddDesenvlvida(atividade) == 1){
	
		printf("\n\nAtividade excluida com sucesso!");
	} else{
		printf("\n\nErro ao excluir atividade");
	}

	continuarComEnter("\nPressione [Enter] para continuar...\n");
}

/*
	Objetivo: Remover uma atividade desenvolvida
	Parametros: a struct da atividade a ser removida
	Retorno: nenhum
*/

int removeAtvddDesenvlvida(AtividadeDesenvolvida atividade){
	FILE *arqv, *arqvAux;
	int excluido=1;
	AtividadeDesenvolvida atvddLida;

	arqv = fopen(NOME_ARQ_ATIVDESEV, "rb");

	if(arqv != NULL){
		arqvAux = fopen("arqv_aux.bin", "wb");

		if(arqvAux != NULL){
		
			while(!feof(arqv)){
				if(fread(&atvddLida, sizeof(AtividadeDesenvolvida), 1, arqv) == 1){
					if(atvddLida.matriculaFrequentador != atividade.matriculaFrequentador
					   || atvddLida.identificadorSerie != atividade.identificadorSerie){
					   
						if(fwrite(&atvddLida, sizeof(AtividadeDesenvolvida), 1, arqvAux) != 1){
				
							excluido = 0;
				
							break;
						}
					}
				} else{
					break;
			
				}
			}
			fclose(arqvAux);
		} else{
			excluido = 0;
		}

		fclose(arqv);
	} else{
		excluido = 0;
	}

	if(excluido == 1){
		if(remove(NOME_ARQ_ATIVDESEV) == 0){
			if(rename("arqv_aux.bin", NOME_ARQ_ATIVDESEV) != 0){
				excluido = 0;
			}
		} else {
			excluido = 0;
		}
	}
	
	return excluido;
}
