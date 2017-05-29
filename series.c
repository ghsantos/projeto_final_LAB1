#include "series.h"

/*
	Objetivo: Obter a qtd de series de exercicios cadastradas
	Parametros: nenhum
	Retorno: qtd de series cadastradas
*/
int obtemQtdSeriesCadastradas(void){
	FILE *arq;
	int qtdSeries=0;
	
	arq = fopen(NOME_ARQ_SERIEEX, "rb");
	if(arq != NULL){
		if(fseek(arq, 0, SEEK_END) == 0){
			qtdSeries = ftell(arq) / sizeof(SerieExercicio);
		}
		fclose(arq);
	}
	
	return qtdSeries;
}

/*
	Objetivo: Obter a posicao dos dados de uma serie de exercicio dentro
		de um arquivo de entrada
	Parametros: codigo identificador da serie
	Retorno: 0(se nada foi encontrado) ou o nro correspondente a posicao da serie
*/
int obtemPosicaoSerieArq(int identificadorSeriePesq){
	SerieExercicio serieExercicio;
	FILE *arq;
	int contSeries=0, posicaoSerieArq=0;
	
	arq = fopen(NOME_ARQ_SERIEEX, "rb");
	if(arq != NULL){
		while(feof(arq) == 0){
			if(fread(&serieExercicio, sizeof(SerieExercicio), 1, arq) == 1){
				contSeries++;
				if(serieExercicio.identificadorSerie == identificadorSeriePesq){
					posicaoSerieArq = contSeries;
					break;
				}
			}
		}
		
		fclose(arq);
	}
	
	return posicaoSerieArq;
}

/*
	Objetivo: Obter os dados de uma serie de exercicios a partir da posicao do seus dados
		em um arquivo de entrada
	Parametros: endereco de memoria da struct(serie de exercicios) que vai armazenar os dados,
		posicao dos dados da serie no arquivo de entrada
	Retorno: 0(os dados nao foram recuperados) ou 1(os dados foram recuperados)
*/
int obtemDadosSerieEx(SerieExercicio *serieExercicio, int posicaoSerieArq){
	FILE *arq;
	int serieExEncontrada=0;
	
	arq = fopen(NOME_ARQ_SERIEEX, "rb");
	if(arq != NULL){
		if(fseek(arq, sizeof(SerieExercicio)*(posicaoSerieArq-1), SEEK_SET) == 0){
			if(fread(serieExercicio, sizeof(SerieExercicio), 1, arq) == 1){
				serieExEncontrada=1;
			}
		}
		
		fclose(arq);
	}
	
	return serieExEncontrada;
}

/*
	Objetivo: Apresentar os dados de todas as series de exercicios cadastradas
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaDadosSeriesExs(void){
	FILE *arq;
	SerieExercicio serieExercicio;
	int existeSeriesEx=0;
	
	arq = fopen(NOME_ARQ_SERIEEX, "rb");
	if(arq != NULL){
		printf("%-15.15s%-15.15s %-15.15s%s\n", "Identificador", "Descricao", "Duracao (min)", "Qtd de calorias perdidas");
		while(feof(arq) == 0){
			if(fread(&serieExercicio, sizeof(SerieExercicio), 1, arq) == 1){
				printf("%-15d%-15.15s %-15d%d\n", serieExercicio.identificadorSerie, serieExercicio.descricao, serieExercicio.duracao, serieExercicio.qtdCaloriasPerdidas);
				existeSeriesEx=1;
			}
		}
		
		fclose(arq);
	}
	
	if(existeSeriesEx==0){
		printf("\n\nNao existem series de exercicios cadastradas!");
	}
}

/*
	Objetivo: Apresentar os dados de uma serie de exercicio especifica
	Parametros: endereco de memoria da struct(serie) com os dados a serem exibidos
	Retorno: nenhum
*/
void apresentaDadosSerieEx(SerieExercicio *serieExercicio){
	printf("\nIdentificador: %d\n", serieExercicio->identificadorSerie);
	printf("Descricao: %s\n", serieExercicio->descricao);
	printf("Duracao prevista em minutos: %d\n", serieExercicio->duracao);
	printf("Qtd de calorias a serem perdidas: %d\n", serieExercicio->qtdCaloriasPerdidas);
}

/*
	Objetivo: Cadastrar uma nova serie de exercicios
	Parametros: nenhum
	Retorno: nenhum
*/
void cadastraSerieEx(void){
	SerieExercicio serieExercicio;
	int idSerieRepetido;
	
	apresentaDadosAcademia();
	
	// Coletando o codigo identificador da serie
	serieExercicio.identificadorSerie = leValidaInt("\n\nCod. Identificador da serie: ", "Identificador invalido... Digite novamente: ", VAL_MIN_ID_SERIE, VAL_MAX_ID_SERIE);
	
	// Verificando se o codigo identificador da serie da foi cadastrado
	if(existeSerie(serieExercicio.identificadorSerie) == 1){
		printf("\n\nEssa serie ja foi cadastrada!");
	} else {
		// Coletando a descricao
		leValidaTexto("\nDescricao: ", "Descricao invalida... Digite novamente: ", serieExercicio.descricao, TAM_MIN_DESCRICAO_SERIE, TAM_MAX_DESCRICAO_SERIE);
		
		// Coletando o duracao prevista em minutos e a qtd de calorias a serem perdidas
		serieExercicio.duracao = leValidaInt("\nDuracao (minutos): ", "Duracao invalida... Digite novamente: ", VAL_MIN_DURACAO_SERIE, VAL_MAX_DURACAO_SERIE);
		serieExercicio.qtdCaloriasPerdidas = leValidaInt("\nQuantidade de calorias a serem perdidas: ", "Quantidade invalida... Digite novamente: ", VAL_MIN_CAL_PERDIDAS, VAL_MAX_CAL_PERDIDAS);
		
		// Tentando gravar os dados da nova serie em um arquivo de saida
		if(gravaDadosSerieNova(&serieExercicio) == 0){
			printf("\n\nErro ao tentar cadastrar a serie de exercicio!");
		} else {
			printf("\n\nSerie de exercicio cadastrada com sucesso!");
		}
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Verificar se uma serie de exercicios exixte
	Parametros: Uma struct de serie de exercicios
	Retorno: 1 a serie existe, 0 nao
*/
int existeSerie(int identificadorSerie){
	int existe=0;
	FILE *arqv;
	SerieExercicio serieLida;
	
	arqv = fopen(NOME_ARQ_SERIEEX, "rb");
	if(arqv != NULL){
		while(!feof(arqv)){
			if(fread(&serieLida, sizeof(SerieExercicio), 1, arqv) == 1){
				if(serieLida.identificadorSerie == identificadorSerie){
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
	Objetivo: Gravar os dados de uma nova serie de exercicios em arquivo de saida
	Parametros: endereco de memoria da struct com os dados da serie a ser gravada
	Retorno: 0(ocorreu erros na gravacao) ou 1(gravacao concluida com sucesso)
*/
int gravaDadosSerieNova(SerieExercicio *serieExercicio){
	int gravacaoConcluida=0;
	FILE *arq;
	
	arq = fopen(NOME_ARQ_SERIEEX, "ab");
	if(arq != NULL){
		if(fwrite(serieExercicio, sizeof(SerieExercicio), 1, arq) == 1){
			gravacaoConcluida=1;
		}
		
		fclose(arq);
	}
	
	return gravacaoConcluida;
}


/*
	Objetivo: Alterar os dados de uma serie de exercicio (com excecao do codigo identificador)
	Parametros: nenhum
	Retorno: nenhum
*/
void alteraDadosSerieEx(void){
	SerieExercicio serieExercicio;
	int posicaSerieArq;
	
	apresentaDadosAcademia();
	
	if(obtemQtdSeriesCadastradas() == 0){
		printf("\n\nNao existem series de exercicios cadastradas!");
	} else {
		printf("\n\n");
		apresentaDadosSeriesExs();
		
		// Coletando o codigo identificador da serie a ser alterada
		serieExercicio.identificadorSerie = leValidaInt("\n\nCod. identificador da serie a ser alterada: ", "Identificador invalido... Digite novamente: ", VAL_MIN_ID_SERIE, VAL_MAX_ID_SERIE);
		
		// Verificando se o codigo identificador existe
		posicaSerieArq = obtemPosicaoSerieArq(serieExercicio.identificadorSerie);
		if(posicaSerieArq == 0){
			printf("\n\nIdentificador inexistente!");
		} else {
			// Tentando obter os dados da serie selecionada
			if(obtemDadosSerieEx(&serieExercicio, posicaSerieArq) == 0){
				printf("\n\nErro ao tentar recuperar os dados da serie selecionada!");
			} else {
				// Verificando se o usuario realizou alguma modificacao
				if(modificaSerieEx(&serieExercicio) == 0){
					printf("\n\nNenhum dado da serie foi alterado!");
				} else {
					// Tentando gravar os dados modificados
					if(gravaDadosSerieAlterada(&serieExercicio, posicaSerieArq) == 0){
						printf("\n\nErro ao tentar alterar os dados da serie selecionada!");
					} else {
						printf("\n\nDados alterados com sucesso!");
					}
				}
			}
		}
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Modificar os dados de uma serie
	Parametros: endereco de memoria da serie
	Retorno: 0(nenhum dado foi modificado) ou 1(algum dado foi modificado)
*/
int modificaSerieEx(SerieExercicio *serieExercicio){
	int dadosModificados=0;
	char opcaoDesejada;
	
	LIMPA_TELA;
	apresentaDadosAcademia();
	apresentaDadosSerieEx(serieExercicio);
	opcaoDesejada = leValidaOpcao("\n\nDeseja alterar os dados dessa serie[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
	
	if(opcaoDesejada == 'S'){
		dadosModificados=1;
		printf("\n\nAlteracoes Possiveis: \n");
		printf("D - Descricao\n");
		printf("M - Duracao prevista em minutos\n");
		printf("Q - Qtd de calorias a serem perdidas\n");
		printf("Z - Cancelar alteracoes\n\n");
		opcaoDesejada = leValidaOpcao("Opcao desejada: ", "Opcao invalida... Digite novamente: ", "DMQZ");
		
		switch(opcaoDesejada){
			case 'D':{
				leValidaTexto("\nNova descricao: ", "Descricao invalida... Digite novamente: ", serieExercicio->descricao, TAM_MIN_DESCRICAO_SERIE, TAM_MAX_DESCRICAO_SERIE);
				break;
			}
			
			case 'M':{
				serieExercicio->duracao = leValidaInt("\nNova duracao: ", "Duracao invalida... Digite novamente: ", VAL_MIN_DURACAO_SERIE, VAL_MAX_DURACAO_SERIE);
				break;
			}
			
			case 'Q':{
				serieExercicio->qtdCaloriasPerdidas = leValidaInt("\nNova qtd de calorias perdidas: ", "Qtd invalida... Digite novamente: ", VAL_MIN_CAL_PERDIDAS, VAL_MAX_CAL_PERDIDAS);
				break;
			}
			
			case 'Z':{
				dadosModificados=0;
				break;
			}
		}
	}
	
	return dadosModificados;
}

/*
	Objetivo: Gravar os dados alterados de uma serie de exercicio no arquivo de saida
	Parametros: endereco de memoria da struct com os dados, posicao da serie no arquivo
	Retorno: 0(erro na gravacao) ou 1(gravacao concluida)
*/
int gravaDadosSerieAlterada(SerieExercicio *serieExercicio, int posicaoSerieArq){
	FILE *arq;
	int gravacaoConcluida=0;
	
	arq = fopen(NOME_ARQ_SERIEEX, "rb+");
	if(arq != NULL){
		if(fseek(arq, sizeof(SerieExercicio)*(posicaoSerieArq-1), SEEK_SET) == 0){
			if(fwrite(serieExercicio, sizeof(SerieExercicio), 1, arq) == 1){
				gravacaoConcluida=1;
			}
		}
		
		fclose(arq);
	}
	
	return gravacaoConcluida;
}


/*
	Objetivo: Excluir uma serie de exercicios
	Parametros: nenhum
	Retorno: nenhum
*/
void excluiSerieEx(void){
	SerieExercicio serieExercicio;
	int posicaSerieArq;
	char opcaoDesejada;
	
	apresentaDadosAcademia();
	
	if(obtemQtdSeriesCadastradas() == 0){
		printf("\n\nNao existem series de exercicios cadastradas!");
	} else {
		printf("\n\n");
		apresentaDadosSeriesExs();
		
		// Coletando o codigo identificador da serie a ser excluida
		serieExercicio.identificadorSerie = leValidaInt("\n\nCod. identificador da serie a ser excluida: ", "Identificador invalido... Digite novamente: ", VAL_MIN_ID_SERIE, VAL_MAX_ID_SERIE);
		
		// Verificando se o codigo identificador existe
		posicaSerieArq = obtemPosicaoSerieArq(serieExercicio.identificadorSerie);
		if(posicaSerieArq == 0){
			printf("\n\nIdentificador inexistente!");
		} else {
			// Tentando obter os dados da serie selecionada
			if(obtemDadosSerieEx(&serieExercicio, posicaSerieArq) == 0){
				printf("\n\nErro ao tentar recuperar os dados da serie selecionada!");
			} else {
				// Verificando se a serie selecionada e a que sera excluida
				LIMPA_TELA;
				apresentaDadosAcademia();
				apresentaDadosSerieEx(&serieExercicio);
				opcaoDesejada = leValidaOpcao("\n\nDeseja excluir essa serie de exercicio[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
				
				if(opcaoDesejada == 'N'){
					printf("\n\nNenhum serie de exercicio foi excluida!");
				} else {
					// Verificando se a serie ja foi executada por algum frequentador
					if(verifSerieJaFoiExecutada(serieExercicio.identificadorSerie) == 1){
						printf("\n\nEsta serie nao pode ser excluida!\n");
						printf("Motivo: esta sendo executada por algum frequentador!\n");
					} else {
						// Tentando remover a serie de exercicio
						if(removeDadosSerieArq(serieExercicio.identificadorSerie) == 0){
							printf("\n\nErro ao tentar excluir a serie de exercicio!");
						} else {
							printf("\n\nSerie excluida com sucesso!");
						}
					}
				}
			}
		}
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Verificar se uma determinada serie ja foi executada por algum frequentador
	Parametros: codigo identificador da serie de exercicio
	Retorno: 0(nao foi executada por ninguem) ou 1(ja foi executada)
*/
int verifSerieJaFoiExecutada(int identificadorSeriePesq){
	AtividadeDesenvolvida ativDesenvolvida;
	FILE *arq;
	int jaFoiExecutada=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		while(feof(arq) == 0){
			if(fread(&ativDesenvolvida, sizeof(AtividadeDesenvolvida), 1, arq) == 1){
				if(ativDesenvolvida.identificadorSerie == identificadorSeriePesq){
					jaFoiExecutada=1;
					break;
				}
			}
		}
		
		fclose(arq);
	}
	
	return jaFoiExecutada;
}

/*
	Objetivo: Remover os dados de uma determinada serie de um arquivo de entrada
	Parametros: codigo identificador da serie
	Retorno: 0(nao foi removida) ou 1(removida com sucesso)
*/
int removeDadosSerieArq(int identificadorSerieExc){
	SerieExercicio serieExercicio;
	FILE *arq, *arqAux;
	int remocaoConcluida=1;
	
	arq = fopen(NOME_ARQ_SERIEEX, "rb");
	if(arq != NULL){
		arqAux = fopen("arqSerieAux.bin", "wb");
		if(arqAux != NULL){
			while(feof(arq) == 0){
				if(fread(&serieExercicio, sizeof(SerieExercicio), 1, arq) == 1){
					if(serieExercicio.identificadorSerie != identificadorSerieExc){
						if(fwrite(&serieExercicio, sizeof(SerieExercicio), 1, arqAux) != 1){
							remocaoConcluida=0;
							break;
						}
					}
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
		if(remove(NOME_ARQ_SERIEEX) == 0){
			if(rename("arqSerieAux.bin", NOME_ARQ_SERIEEX) != 0){
				remocaoConcluida=0;
			}
		} else {
			remocaoConcluida=0;
		}
	}
	
	return remocaoConcluida;
}
