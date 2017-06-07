#include "atividades.h"

/*
	Objetivo: Apresentar os dados de todas as atividades desenvolvidas cadastradas
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaDadosAtividadesArq(void){
	AtividadeDesenvolvida ativDesenvolvida;
	FILE *arq;
	int existeAtividades=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		printf("%-18.18s%-10.10s%s\n", "Matricula Freq.", "Id Serie", "Data e hora do inicio");
		while(feof(arq) == 0){
			if(fread(&ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
				printf("%-18d%-10d", ativDesenvolvida.matriculaFrequentador, ativDesenvolvida.identificadorSerie);
				printf("%02d/%02d/%d ", ativDesenvolvida.dataInicio.dia, ativDesenvolvida.dataInicio.mes, ativDesenvolvida.dataInicio.ano);
				printf("%02d:%02d\n", ativDesenvolvida.horarioInicio.hora, ativDesenvolvida.horarioInicio.minutos);
				existeAtividades=1;
			}
		}
		
		fclose(arq);
	}
	
	if(existeAtividades == 0){
		printf("Nao existem atividades cadastradas!");
	}
}

/*
	Objetivo: Apresentar os dados de das atividades armazenadas em memoria
	Parametros: o endereco inicial do vetor de atividades e a qtd de atividades
	Retorno: nenhum
*/
void apresentaDadosAtividadesMemoria(AtividadeDesenvolvida *atividades, int qtdAtividades){
	int cont;
	
	printf("%-18.18s%-10.10s%s\n", "Matricula Freq.", "Id Serie", "Data e hora do inicio");
	
	for(cont=0; cont<qtdAtividades; ++cont){
		printf("%-18d%-10d", atividades[cont].matriculaFrequentador, atividades[cont].identificadorSerie);
		printf("%02d/%02d/%d ", atividades[cont].dataInicio.dia, atividades[cont].dataInicio.mes, atividades[cont].dataInicio.ano);
		printf("%02d:%02d\n", atividades[cont].horarioInicio.hora, atividades[cont].horarioInicio.minutos);
	}
}

/*
	Objetivo: Apresentar os dados de todas as atividades desenvolvidas cadastradas com
		um indice seletor
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaDadosAtividadesArqIndice(void){
	AtividadeDesenvolvida ativDesenvolvida;
	FILE *arq;
	int existeAtividades=0, cont=1;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		printf("%-8.8s%-18.18s%-10.10s%s\n", "Indice", "Matricula Freq.", "Id Serie", "Data e hora do inicio");
		while(feof(arq) == 0){
			if(fread(&ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
				printf("%-8d", cont);
				printf("%-22d%-10d", ativDesenvolvida.matriculaFrequentador, ativDesenvolvida.identificadorSerie);
				printf("%02d/%02d/%d ", ativDesenvolvida.dataInicio.dia, ativDesenvolvida.dataInicio.mes, ativDesenvolvida.dataInicio.ano);
				printf("%02d:%02d\n", ativDesenvolvida.horarioInicio.hora, ativDesenvolvida.horarioInicio.minutos);
				existeAtividades=1;
				++cont;
			}
		}
		
		fclose(arq);
	}
	
	if(existeAtividades == 0){
		printf("\n\nNao existem atividades cadastradas!");
	}
}

/*
	Objetivo: Apresentar todas as atividades desenvolvidas por um frequentador
	Parametros: matricula do frequentador
	Retorno: nenhum
*/
void apresentaAtivsFrequentador(int matriculaPesq){
	AtividadeDesenvolvida ativDesenvolvida;
	FILE *arq;
	int existeAtividades=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		printf("%-18.18s%-10.10s%s\n", "Matricula Freq.", "Id Serie", "Data e hora do inicio");
		while(feof(arq) == 0){
			if(fread(&ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
				if(ativDesenvolvida.matriculaFrequentador == matriculaPesq){
					printf("%-22d%-10d", ativDesenvolvida.matriculaFrequentador, ativDesenvolvida.identificadorSerie);
					printf("%02d/%02d/%d ", ativDesenvolvida.dataInicio.dia, ativDesenvolvida.dataInicio.mes, ativDesenvolvida.dataInicio.ano);
					printf("%02d:%02d\n", ativDesenvolvida.horarioInicio.hora, ativDesenvolvida.horarioInicio.minutos);
					existeAtividades=1;
				}
			}
		}
		
		fclose(arq);
	}
	
	if(existeAtividades == 0){
		printf("Nenhuma atividade foi encontrada!\n");
	}
}

/*
	Objetivo: Obter a posicao dos dados de uma atividade desenvolvida em um arquivo
	Parametros: matricula do frequentador e o cod. identificador da serie de exercicio
	Retorno: 0(se nada foi encontrado) ou o nro correspondente a posicao da atividade desenvolvida
*/
int obtemPosicaoAtivDesenvArq(int matricFreqPesq, int idSerieExPesq){
	AtividadeDesenvolvida ativDesenvolvida;
	FILE *arq;
	int contAtivs=0, posicaoAtivArq=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		while(feof(arq) == 0){
			if(fread(&ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
				contAtivs++;
				if(ativDesenvolvida.matriculaFrequentador == matricFreqPesq && ativDesenvolvida.identificadorSerie == idSerieExPesq){
					posicaoAtivArq=contAtivs;
					break;
				}
			}
		}
		
		fclose(arq);
	}
	
	return posicaoAtivArq;	
}

/*
	Objetivo: Obter a qtd de atividades desenvolvidas cadastradas
	Parametros: nenhum
	Retorno: qtd encontrada
*/
int obtemQtdAtivDesevCadastradas(void){
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
	Objetivo: Obter os dados de uma atividade desenvolvida a partir da sua chave unica
	Parametros: endereco de memoria da struct com os dados da atividade
	Retorno: 0(nao foi encontrada) ou 1(atividade encontrada)
*/
int obtemDadosAtivPorChaveUnica(AtividadeDesenvolvida *ativDesenvPesq){
	
	AtividadeDesenvolvida ativDesenvLida;
	FILE *arq;
	int ativEncontrada=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		while(feof(arq) == 0){
			if(fread(&ativDesenvLida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
				if(ativDesenvLida.matriculaFrequentador == ativDesenvPesq->matriculaFrequentador &&
					ativDesenvLida.identificadorSerie == ativDesenvPesq->identificadorSerie &&
					ativDesenvLida.dataInicio.dia == ativDesenvPesq->dataInicio.dia && ativDesenvLida.dataInicio.mes == ativDesenvPesq->dataInicio.mes &&
					ativDesenvLida.dataInicio.ano == ativDesenvPesq->dataInicio.ano){
						ativDesenvPesq->horarioInicio = ativDesenvLida.horarioInicio;
						ativEncontrada=1;
						break;
					}
			}
		}
		
		fclose(arq);
	}
	
	return ativEncontrada;
}


/*
	Objetivo: Obter os dados de uma atividade desenvolvida a partir da sua posicao em um arquivo de entrada
	Parametros: endereco de memoria da struct que vai armazenar os dados, posicao dos dados no arquivo
	Retorno: 0(os dados nao foram recuperados) ou 1(dados recuperados com sucesso)
*/
int obtemDadosAtivPorPosicaoArq(AtividadeDesenvolvida *ativDesenvolvida, int posicaAtivDesevArq){
	FILE *arq;
	int ativDesevEncontrada=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		if(fseek(arq, sizeof(AtividadeDesenvolvida)*(posicaAtivDesevArq-1), SEEK_SET) == 0){
			if(fread(ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
				ativDesevEncontrada=1;
			}
		}
		
		fclose(arq);
	}
	
	return ativDesevEncontrada;
}

/*
	Objetivo: Apresentar os dados de uma atividade desenvolvida especifica
	Parametros: endereco de memoria da struct com os dados da atividade
	Retorno: nenhum
*/
void apresentaDadosAtivDesenvolvida(AtividadeDesenvolvida *ativDesenvolvida){
	printf("\nMatricula do frequentador: %d\n", ativDesenvolvida->matriculaFrequentador);
	printf("Cod. Identificador da serie de exercicio: %d\n", ativDesenvolvida->identificadorSerie);
	printf("Data de inicio da atividade: %02d/%02d/%d\n", ativDesenvolvida->dataInicio.dia, ativDesenvolvida->dataInicio.mes, ativDesenvolvida->dataInicio.ano);
	printf("Hora de inicio da atividade: %02d:%02d\n", ativDesenvolvida->horarioInicio.hora, ativDesenvolvida->horarioInicio.minutos);
}

/*
	Objetivo: Verificar se um frequentador ja fez uma atividade hoje
	Parametros: a struct da atividade desenvolvida
	Retorno: 1 se o frequentador fez, 0 caso contrario
*/
int verifFreqFezAtividadeHoje(AtividadeDesenvolvida atividade){
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
	Objetivo: Verificar se um determinado frequentador ja executou alguma serie de exercicios (Atividade desenvolvidas)
	Parametros: matricula do frequentador
	Retorno: 0(nao existem atividades cadastradas) ou 1(ja executou alguma atividade)
*/
int verifFreqFezAlgumaAtividade(int matriculaVerif){
	AtividadeDesenvolvida ativDesenvolvida;
	FILE *arq;
	int jaDesenvolveuAtiv=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		while(feof(arq) == 0){
			if(fread(&ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
				if(ativDesenvolvida.matriculaFrequentador == matriculaVerif){
					jaDesenvolveuAtiv=1;
					break;
				}
			}
		}
		
		fclose(arq);
	}
	
	return jaDesenvolveuAtiv;
}
/*
	Objetivo: Cadastrar uma nova atividade a ser desenvolvida
	Parametros: nenhum
	Retorno: nenhum
*/
void cadastraAtivDesenvolvida(void){
	AtividadeDesenvolvida ativDesenvolvida;
	char opcaoDesejada;
	
	apresentaDadosAcademia();
	printf("\n");
	
	// Verificando se existem frequentadores cadastrados
	if(obtemQtdFreqCadastrados() == 0){
		printf("Nao existem frequentadores cadastrados!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		return;
	}
	
	// Verificando se existem series de exercicios cadastradas
	if(obtemQtdSeriesCadastradas() == 0){
		printf("Nao existem series de exercicios cadastradas!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		return;
	}
	
	// Se existirem frequentadores e series cadastradas
	// Obtendo o matricula do frequentador
	apresentaDadosFrequentadoresArq();
	ativDesenvolvida.matriculaFrequentador = leValidaInt("\n\nDigite a matricula do frequentador desejado: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
	
	// Verificando se a matricula existe
	if(obtemPosicaoFreqArq(ativDesenvolvida.matriculaFrequentador) == 0){
		printf("\n\nNao foi encontrado nenhum frequentador com essa matricula!");
	} else {
		// Obtendo o codigo identificador da serie de exercicio
		LIMPA_TELA;
		apresentaDadosAcademia();
		printf("\n");
		apresentaDadosSeriesExsArq();
		
		ativDesenvolvida.identificadorSerie = leValidaInt("\n\nCod. identificador da serie desejada: ", "Identificador invalido... Digite novamente: ", VAL_MIN_ID_SERIE, VAL_MAX_ID_SERIE);
		ativDesenvolvida.dataInicio = obtemDataSistema();
		ativDesenvolvida.horarioInicio = obtemHoraSistema();
		
		// Verificando se o codigo identificador existe
		if(obtemPosicaoSerieArq(ativDesenvolvida.identificadorSerie) == 0){
			printf("\n\nNao foi encontrada nenhum serie com esse cod. identificador!");
		} else if(verifFreqFezAtividadeHoje(ativDesenvolvida) == 1){ // Verificando se o frequentador ja realizou essa atividade no dia
			printf("\n\nEssa atividade nao pode ser cadastrada!\n");
			printf("Motivo: o frequentador ja realizou esta atividade hoje.");
		} else {
			LIMPA_TELA;
			apresentaDadosAcademia();
			apresentaDadosAtivDesenvolvida(&ativDesenvolvida);
			opcaoDesejada = leValidaOpcao("\n\nDeseja cadastrar essa atividade[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
			
			if(opcaoDesejada == 'N'){
				printf("\n\nCadastro cancelado!");
			} else {
				// Tentando gravar os dados da atividade
				if(gravaDadosAtivDesenvolvidaArq(&ativDesenvolvida) == 0){
					printf("\n\nErro ao tentar cadastrar a atividade desenvolvida!");
				} else {
					printf("\n\nAtividade desenvolvida cadastrada com sucesso!");
				}
			}
		}
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Gravar os dados de uma atividade desenvolvida em um arquivo de saida
	Parametros: endereco de memoria da struct com os dados da atividade desenvolvida
	Retorno: 1 se os dados foram gravados corretamente, 0 caso contrario
*/
int gravaDadosAtivDesenvolvidaArq(AtividadeDesenvolvida *ativDesenvolvida){
	FILE *arq;
	int gravacaoConcluida=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "ab");
	if(arq != NULL){
		if(fwrite(ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
			gravacaoConcluida=1;
		}
		fclose(arq);
	}
	
	return gravacaoConcluida;
}

/*
	Objetivo: Excluir uma atividade desenvolvida
	Parametros: nenhum
	Retorno: nenhum
*/
void excluiAtivDesenvolvida(void){
	AtividadeDesenvolvida ativDesenvolvida;
	char opcaoDesejada;
	int qtdAtivDesevCadastradas, indice;
	
	apresentaDadosAcademia();
	printf("\n");
	
	// Verificando se existem atividades desenvolvidas cadastradas
	qtdAtivDesevCadastradas = obtemQtdAtivDesevCadastradas();
	
	if(qtdAtivDesevCadastradas == 0){
		printf("\nNao existem atividades desenvolvidas cadastradas!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		return;
	}
	
	
	apresentaDadosAtividadesArqIndice();
	
	// Coletando indice do frequentador
	indice = leValidaInt("\n\nDigite o indice da atividade a ser excluida: ", "Indice inexistente... Digite novamente: ", 1, qtdAtivDesevCadastradas);
	
	// Obtendo as informacoes da atividade
	if(obtemDadosAtivPorPosicaoArq(&ativDesenvolvida, indice) == 0){
		printf("\n\nNao foi possivel recuperar os dados da atividade selecionada!");
	} else {
		LIMPA_TELA;
		apresentaDadosAcademia();
		apresentaDadosAtivDesenvolvida(&ativDesenvolvida);
		opcaoDesejada = leValidaOpcao("\n\nDeseja excluir essa atividade desenvolvida[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
		
		if(opcaoDesejada == 'N'){
			printf("\n\nExclusao cancelada!");
		} else {
			// Tentando remover os dados da atividade do arquivo de entrada
			if(removeDadosAtivDesevArq(indice) == 0){
				printf("\n\nErro ao tentar excluir a atividade desenvolvida!");
			} else {
				printf("\n\nAtividade desenvolvida excluida com sucesso!");
			}
		}
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Remover uma atividade desenvolvida de um arquivo de entrada
	Parametros: matricula do frequentador e o id da serie de exercicio vinculada a atividade
	Retorno: 0(ocorreu erro na exclusao) ou 1(exclusao concluida com sucesso)
*/
int removeDadosAtivDesevArq(int indice){
	AtividadeDesenvolvida ativDesenvolvida;
	FILE *arq, *arqAux;
	int remocaoConcluida=1, cont=1;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		arqAux = fopen("arqAtivDesevAux.bin", "wb");
		if(arqAux != NULL){
			while(feof(arq) == 0){
				if(fread(&ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
					if(cont != indice){
						if(fwrite(&ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arqAux) != 1){
							remocaoConcluida=0;
							break;
						}
					}
					++cont;
				}
			}
			
			fclose(arqAux);
		} else {
			remocaoConcluida=0;
		}
		fclose(arq);
	} else {
		remocaoConcluida=0;
	}
	
	if(remocaoConcluida == 1){
		if(remove(NOME_ARQ_ATIVDESEV) == 0){
			if(rename("arqAtivDesevAux.bin", NOME_ARQ_ATIVDESEV) != 0){
				remocaoConcluida=0;
			}
		} else {
			remocaoConcluida=0;
		}
	}
	
	return remocaoConcluida;
}

/*
	Objetivo: Pesquisar uma atividade desenvolvida pelas suas chaves unicas
	Parametros: nenhum
	Retorno: nenhum
*/
void pesqAtivDesevPelaChaveUnica(void){
	AtividadeDesenvolvida ativDesenvolvida;
	
	apresentaDadosAcademia();
	
	// Verificando se existem atividades cadastradas
	if(obtemQtdAtivDesevCadastradas() == 0){
		printf("\n\nNao existem atividades desenvolvidas cadastradas!");
		return;
	}
	
	// Caso existam atividades cadastradas
	printf("\n");
	apresentaDadosAtividadesArq();
	ativDesenvolvida.matriculaFrequentador = leValidaInt("\n\nMatricula do frequentador que executou a atividade: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
	
	// Verificando se o freq. informado ja executou alguma atividade
	if(verifFreqFezAlgumaAtividade(ativDesenvolvida.matriculaFrequentador) == 0){
		printf("\n\nEste frequentador nao executou nenhum atividade!");
	} else {
		LIMPA_TELA;
		apresentaDadosAcademia();
		printf("\n");
		apresentaAtivsFrequentador(ativDesenvolvida.matriculaFrequentador);
		
		ativDesenvolvida.identificadorSerie = leValidaInt("\n\nCod. identificador da serie desejada: ", "Identificador invalido... Digite novamente: ", VAL_MIN_ID_SERIE, VAL_MAX_ID_SERIE);
		
		ativDesenvolvida.dataInicio = leValidaData("\nData de inicio");
		
		if(obtemDadosAtivPorChaveUnica(&ativDesenvolvida) == 0){
			printf("\n\nNenhum atividade foi encontrada!");
		} else {
			LIMPA_TELA;
			apresentaDadosAcademia();
			printf("\nAtividade encontrada: \n");
			apresentaDadosAtivDesenvolvida(&ativDesenvolvida);
		}
	}
}
