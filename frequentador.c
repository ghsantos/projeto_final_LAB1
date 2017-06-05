#include "frequentador.h"

/*
	Objetivo: Obter a qtd de frequentadores cadastrados
	Parametros: nenhum
	Retorno: qtd de cadastros
*/
int obtemQtdFreqCadastrados(void){
	FILE *arq;
	int qtdFrequentadores=0;
	
	arq = fopen(NOME_ARQ_FREQ, "rb");
	if(arq != NULL){
		if(fseek(arq, 0, SEEK_END) == 0){
			qtdFrequentadores = ftell(arq) / sizeof(Frequentador);
		}
		fclose(arq);
	}
	
	return qtdFrequentadores;
}

/*
	Objetivo: Obter a posicao dos dados de um frequentador dentro de um arquivo
		de entrada
	Parametros: matricula do frequentador
	Retorno: 0(se nada foi encontrada) ou o nro correspondente a posicao do frequentador
*/
int obtemPosicaoFreqArq(int matriculaPesq){
	Frequentador frequentador;
	FILE *arq;
	int contFreq=0, posicaoFreqArq=0;
	
	arq = fopen(NOME_ARQ_FREQ, "rb");
	if(arq != NULL){
		while(feof(arq) == 0){
			if(fread(&frequentador, sizeof(Frequentador), 1, arq) == 1){
				contFreq++;
				if(frequentador.matricula == matriculaPesq){
					posicaoFreqArq=contFreq;
					break;
				}
			}
		}
		
		fclose(arq);
	}
	
	return posicaoFreqArq;
}

/*
	Objetivo: Obter os dados de um frequentador a partir da sua posicao dentro de um arquivo de entrada
	Parametros: endereco de memoria da struct(frequentador) que vai armazenar os dados, posicao dos dados
		do frequentador no arquivo
	Retorno: 0(os dados nao foram recuperados) ou 1(os dados foram recuperados com exito)
*/
int obtemDadosFreqPorPosicaoArq(Frequentador *frequentador, int posicaoFreqArq){
	FILE *arq;
	int freqEncontrado=0;
	
	arq = fopen(NOME_ARQ_FREQ, "rb");
	if(arq != NULL){
		if(fseek(arq, sizeof(Frequentador)*(posicaoFreqArq-1), SEEK_SET) == 0){
			if(fread(frequentador, sizeof(Frequentador), 1, arq) == 1){
				freqEncontrado=1;
			}
		}
		
		fclose(arq);
	}
	
	return freqEncontrado;
}

/*
	Objetivo: Obter os dados de um frequentador a partir da sua matricula armazenada em um arquivo de entrada
	Parametros: endereco de memoria da struct que vai armazenar os dados, matricula do frequentador
	Retorno: 0(os dados nao foram recuperados) ou 1(os dados foram recuperados com exito)
*/
int obtemDadosFreqPorMatric(Frequentador *frequentador, int matriculaPesq){
	FILE *arq;
	int freqEncontrado=0;
	
	arq = fopen(NOME_ARQ_FREQ, "rb");
	if(arq != NULL){
		while(feof(arq) == 0){
			if(fread(frequentador, sizeof(Frequentador), 1, arq) == 1){
				if(frequentador->matricula == matriculaPesq){
					freqEncontrado=1;
					break;
				}
			}
		}
		
		fclose(arq);
	}
	
	return freqEncontrado;
}

/*
	Objetivo: Apresentar os dados de todos os frequentadores armazenados em um
		arquivo de entrada
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaDadosFrequentadoresArq(void){
	FILE *arq;
	Frequentador frequentador;
	int existeFreq=0;
	
	arq = fopen(NOME_ARQ_FREQ, "rb");
	if(arq != NULL){
		printf("%-10.10s%-15.15s%-13.13s%-11.11s%s\n", "Matricula", "Nome", "CPF", "Sexo", "Peso (kg)");
		while(feof(arq) == 0){
			if(fread(&frequentador, sizeof(Frequentador), 1, arq) == 1){
				printf("%-10d%-14.14s %-13.13s", frequentador.matricula, frequentador.nome, frequentador.cpf);
				printf("%-11.11s", frequentador.sexo == 'M' ? "Masculino" : "Feminino");
				printf("%.2f\n", frequentador.peso);
				existeFreq=1;
			}
		}
		fclose(arq);
	}
	
	if(existeFreq == 0){
		printf("Nao existem frequentadores cadastrados!\n");
	}
}

/*
	Objetivo: Apresentar os dados de todos os frequentadores armazenados em memoria
	Parametros: endereco de memoria incial de vetor de frequentadores, qtd de frequentadores
	Retorno: nenhum
*/
void apresentaDadosFrequentadoresMemoria(Frequentador *frequentadores, int qtdFreq){
	int cont;
	
	printf("%-10.10s%-15.15s%-13.13s%-11.11s%s\n", "Matricula", "Nome", "CPF", "Sexo", "Peso (kg)");
	
	for(cont=0; cont<qtdFreq; cont++){
		printf("%-10d%-14.14s %-13.13s", frequentadores[cont].matricula, frequentadores[cont].nome, frequentadores[cont].cpf);
		printf("%-11.11s", frequentadores[cont].sexo == 'M' ? "Masculino" : "Feminino");
		printf("%.2f\n", frequentadores[cont].peso);
	}
}

/*
	Objetivo: Apresentar os dados de um frequentador armazenado em memoria
	Parametros: endereco de memoria da struct com os dados a serem exibidos
	Retorno: nenhum
*/
void apresentaDadosFrequentador(Frequentador *frequentador){
	printf("\nMatricula: %d\n", frequentador->matricula);
	printf("Nome: %s\n", frequentador->nome);
	printf("CPF: %s\n", frequentador->cpf);
	printf("Peso: %.2f Kg\n", frequentador->peso);
	printf("Sexo: %s\n", frequentador->sexo == 'M' ? "Masculino" : "Feminino");
	printf("Data de ingresso na academia: %02d/%02d/%d\n", frequentador->dataIngresso.dia, frequentador->dataIngresso.mes, frequentador->dataIngresso.ano);
}

/*
	Objetivo: Cadastrar um frequentador gravando os seus dados em um arquivo de saida
	Parametros: nenhum
	Retorno: nenhum
*/
void cadastraFrequentador(void){
	Frequentador frequentador;
	int cpfValido;
	
	apresentaDadosAcademia();
	printf("\nCADASTRAR FREQUENTADOR\n\n");
	
	// Gerando uma matricula aleatorio (unica)
	do{
		frequentador.matricula = geraNroIntAleatorio(VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
	}while(obtemPosicaoFreqArq(frequentador.matricula) != 0);
	printf("Matricula gerada: %d\n", frequentador.matricula);
	
	// Obtendo o nome
	leValidaTexto("\nNome completo: ", "Nome invalido... Digite novamente: ", frequentador.nome, TAM_MIN_NOME_FREQ, TAM_MAX_NOME_FREQ);
	
	// Lendo e validando o CPF
	do{
		leValidaTexto("\nCPF (apenas nros): ", "CPF invalido... Digite os 11 digitos: ", frequentador.cpf, (TAM_CPF-1), TAM_CPF);
		cpfValido = verifCPFValido(frequentador.cpf);
		
		if(cpfValido == 0){
			printf("CPF invalido! Digite novamente!\n");
		}
	}while(cpfValido == 0);
	
	// Obtendo o peso
	frequentador.peso = leValidaFloat("\nPeso (Kg): ", "Peso invalido... Digite novamente: ", VAL_MIN_PESO, VAL_MAX_PESO);
	
	// Obtendo o sexo
	frequentador.sexo = leValidaOpcao("\nSexo[M/f]: ", "Sexo invalido... Digite apenas M ou F: ", "MF");
	
	// Obtendo a data de ingresso na academia (data atual do sistema)
	frequentador.dataIngresso = obtemDataSistema();
	
	// Gravando os dados coletados em um arquivo de saida
	if(gravaDadosFreqNovo(&frequentador) == 0){
		printf("\n\nErro ao tentar cadastrar o frequentador!");
	} else {
		printf("\n\nFrequentador cadastrado com sucesso!");
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Gravar os dados de um novo frequentador em um arquivo
	Parametros: endereco de memoria da struct com os dados do frequentador
	Retorno: 0(erro no cadastro) ou 1(cadastro concluido)
*/
int gravaDadosFreqNovo(Frequentador *frequentador){
	FILE *arq;
	int gravacaoConcluida=0;
	
	arq = fopen(NOME_ARQ_FREQ, "ab");
	if(arq != NULL){
		if(fwrite(frequentador, sizeof(Frequentador), 1, arq) == 1){
			gravacaoConcluida=1;
		}
		fclose(arq);
	}
	
	return gravacaoConcluida;
}

/*
	Objetivo: Alterar os dados de um frequentador (com excecao da matricula)
	Parametros: nenhum
	Retorno: nenhum
*/
void alteraDadosFrequentador(void){
	Frequentador frequentador;
	int posicaoFreqArq;
	
	apresentaDadosAcademia();
	
	// Verificando se tem frequentadores cadastrados
	if(obtemQtdFreqCadastrados() == 0){
		printf("\n\nNao existem frequentadores cadastrados!\n");
	} else {
		printf("\n\n");
		apresentaDadosFrequentadoresArq();
		frequentador.matricula = leValidaInt("\n\nMatricula do frequentador a ser alterado: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
		
		// Verificando se a matricula existe
		posicaoFreqArq = obtemPosicaoFreqArq(frequentador.matricula);
		if(posicaoFreqArq == 0){
			printf("\n\nNao foi encontrado nenhum frequentador com essa matricula!");
		} else {
			// Obtendo os dados do frequentador selecionado
			if(obtemDadosFreqPorPosicaoArq(&frequentador, posicaoFreqArq) == 0){
				printf("\n\nErro ao tentar recuperar os dados do frequentador selecionado!");
			} else {
				// Verificando se o usuario modificou algum dado do frequentador
				if(modificaFrequentador(&frequentador) == 0){
					printf("\n\nNenhum dado foi modificado!");
				} else {
					// Tentando gravar os novos dados do frequentador
					if(gravaDadosFreqAlterado(&frequentador, posicaoFreqArq) == 0){
						printf("\n\nErro ao tentar alterar os dados");
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
	Objetivo: Modificar os dados de um frequentador
	Parametros: endereco de memoria da struct com os dados do frequentador
	Retorno: 0(nao houve alteracao nos dados) ou 1(houve alteracao nos dados)
*/
int modificaFrequentador(Frequentador *frequentador){
	char opcaoDesejada;
	int dadosModificados=0, dadoValido;
	
	LIMPA_TELA;
	apresentaDadosAcademia();
	apresentaDadosFrequentador(frequentador);
	opcaoDesejada = leValidaOpcao("\n\nDeseja alterar os dados desse frequentador[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
	
	if(opcaoDesejada == 'S'){
		dadosModificados=1;
		printf("\n\nAlteracoes Possiveis: \n");
		printf("N - Nome\n");
		printf("C - CPF\n");
		printf("P - Peso\n");
		printf("S - Sexo\n");
		printf("D - Data de ingresso\n");
		printf("Z - Cancelar alteracao\n\n");
		opcaoDesejada = leValidaOpcao("Opcao desejada: ", "Opcao invalida... Digite novamente: ", "NCPSDZ");
		
		switch(opcaoDesejada){
			case 'N':{
				leValidaTexto("\nNovo nome: ", "Nome invalido... Digite ao menos 3 caracteres: ", frequentador->nome, TAM_MIN_NOME_FREQ, TAM_MAX_NOME_FREQ);
				break;
			}
				
			case 'C':{
				do{
					leValidaTexto("\nNovo CPF (apenas nros): ", "CPF invalido... Digite os 11 digitos: ", frequentador->cpf, (TAM_CPF-1), TAM_CPF);
					dadoValido = verifCPFValido(frequentador->cpf);
					
					if(dadoValido == 0){
						printf("CPF invalido! Digite novamente!\n");
					}
				}while(dadoValido == 0);
				break;
			}
			
			case 'P':{
				frequentador->peso = leValidaFloat("\nNovo peso: ", "Peso invalido... Digite novamente: ", VAL_MIN_PESO, VAL_MAX_PESO);
				break;
			}
			
			case 'S':{
				frequentador->sexo = leValidaOpcao("\nNovo sexo[M/f]: ", "Opcao invalida... Digite apenas M ou F: ", "MF");
				break;
			}
			
			case 'D':{
				do{
					printf("\nNova data de ingresso\n");
					frequentador->dataIngresso.dia = leValidaInt("Dia: ", "Dia invalido... Digite novamente: ", 1, 31);
					frequentador->dataIngresso.mes = leValidaInt("\nMes: ", "Mes invalido... Digite novamente: ", 1, 12);
					frequentador->dataIngresso.ano = leValidaInt("\nAno: ", "Ano invalido... Digite novamente: ", 1901, 2037);
					dadoValido = verifDataValida(frequentador->dataIngresso);
					
					if(dadoValido == 0){
						printf("\nData invalida... Digite novamente!");
					}
				}while(dadoValido == 0);
				
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
	Objetivo: Gravar os dados alterados de um frequentador no arquivo de saida
	Parametros: endereco de memoria da struct com os dados, posicao do frequentador no arquivo
	Retorno: 0(erro na gravacao) ou 1(gravacao concluida)
*/
int gravaDadosFreqAlterado(Frequentador *frequentador, int posicaoFreqArq){
	FILE *arq;
	int gravacaoConcluida=0;
	
	arq = fopen(NOME_ARQ_FREQ, "rb+");
	if(arq != NULL){
		if(fseek(arq, sizeof(Frequentador)*(posicaoFreqArq-1), SEEK_SET) == 0){
			if(fwrite(frequentador, sizeof(Frequentador), 1, arq) == 1){
				gravacaoConcluida=1;
			}
		}
		
		fclose(arq);
	}
	
	return gravacaoConcluida;
}

/*
	Objetivo: Excluir um frequentador
	Parametros: nenhum
	Retorno: nenhum
*/
void excluiFrequentador(void){
	Frequentador frequentador;
	char opcaoDesejada;
	
	
	apresentaDadosAcademia();
	
	if(obtemQtdFreqCadastrados() == 0){
		printf("\n\nNao existem frequentadores cadastrados!\n");
	} else {
		printf("\n\n");
		apresentaDadosFrequentadoresArq();
		frequentador.matricula = leValidaInt("\n\nMatricula do frequentador a ser excluido: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
		
		// Verificando se o frequentador existe e obtendo os dados
		if(obtemDadosFreqPorMatric(&frequentador, frequentador.matricula) == 0){
			printf("\n\nNao foi encontrado nenhum frequentador com essa matricula!");
		} else {
			LIMPA_TELA;
			apresentaDadosAcademia();
			apresentaDadosFrequentador(&frequentador);
			opcaoDesejada = leValidaOpcao("\n\nDeseja excluir esse frequentador[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
			
			if(opcaoDesejada == 'N'){
				printf("\n\nNenhum frequentador foi excluido!");
			} else {
				// Verificando se o frequentador ja executou alguma atividade na academia
				if(verifFreqFezAlgumaAtividade(frequentador.matricula) == 1){
					printf("\n\nEsse frequentador nao pode ser excluido!\n");
					printf("Motivo: esse frequentador possui atividades cadastradas!");
				} else {
					// Tentando excluir o frequentador
					if(removeDadosFreqArq(frequentador.matricula) == 0){
						printf("\n\nErro ao tentar excluir o frequentador!");
					} else {
						printf("\n\nFrequentador excluido com sucesso!");
					}
				}
			}
		}
	}
	
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Remover os dados de um determinado frequentador de um arquivo
	Parametros: matricula do frequentador que sera excluido
	Retorno: 0(erro na exclusao) ou 1(exclusao concluida)
*/
int removeDadosFreqArq(int matriculaFreqExc){
	Frequentador frequentador;
	FILE *arq, *arqAux;
	int remocaoConcluida=1;
	
	arq = fopen(NOME_ARQ_FREQ, "rb");
	if(arq != NULL){
		arqAux = fopen("arqFreqAux.bin", "wb");
		if(arqAux != NULL){
			while(feof(arq) == 0){
				if(fread(&frequentador, sizeof(Frequentador), 1, arq) == 1){
					if(frequentador.matricula != matriculaFreqExc){
						if(fwrite(&frequentador, sizeof(Frequentador), 1, arqAux) != 1){
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
	} else{
		remocaoConcluida=0;
	}
	
	if(remocaoConcluida == 1){
		if(remove(NOME_ARQ_FREQ) == 0){
			if(rename("arqFreqAux.bin", NOME_ARQ_FREQ) != 0){
				remocaoConcluida=0;
			}
		} else {
			remocaoConcluida=0;
		}
	}
	
	return remocaoConcluida;
}

/*
	Objetivo: Pesquisar um frequentador pela matricula
	Parametros: nenhum
	Retorno: nenhum
*/
void pesqFrequentadorPelaMatric(void){
	Frequentador frequentador;
	
	apresentaDadosAcademia();
	
	// Verificando se existem frequentadores cadastrados
	if(obtemQtdFreqCadastrados() == 0){
		printf("\n\nNao existem frequentadores cadastrados!\n");
	} else {
		printf("\n");
		apresentaDadosFrequentadoresArq();
		frequentador.matricula = leValidaInt("\n\nMatricula do frequentador a ser pesquisado: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
		
		// Verificando se o frequentador existe e obtendo os dados
		if(obtemDadosFreqPorMatric(&frequentador, frequentador.matricula) == 0){
			printf("\n\nNao foi encontrado nenhum frequentador com essa matricula!");
		} else {
			LIMPA_TELA;
			apresentaDadosAcademia();
			apresentaDadosFrequentador(&frequentador);
		}
	}
}

/*
	Objetivo: Pesquisar frequentadores pelo nome
	Parametros: nenhum
	Retorno: nenhum
*/
void pesqFrequentadoresPeloNome(void){
	FILE *arq;
	char nomeFreqPesq[TAM_MAX_NOME_FREQ], nomeFreqLidoAux[TAM_MAX_NOME_FREQ];
	Frequentador *frequentadores=NULL, *freqAux, freqLido;
	int qtdFreqEncontrados=0, erroPesquisa=0;
	
	// Exibindo os dados auxiliares
	apresentaDadosAcademia();
	printf("\n");
	
	// Verificando se existem frequentadores cadastrados
	if(obtemQtdFreqCadastrados() == 0){
		printf("Nao existem frequentadores cadastrados!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		return;
	}
	
	
	// Caso existam frequentadores
	apresentaDadosFrequentadoresArq();
	
	// Coletando o nome a ser pesquisado
	leValidaTexto("\n\nDigite o nome do frequentador a ser pesquisado: ", "Nome invalido... Digite ao menos 3 caracteres: ", nomeFreqPesq, TAM_MIN_NOME_FREQ, TAM_MAX_NOME_FREQ);
	
	// Transformando o nome para minusculo para facilitar a busca
	toLowerStr(nomeFreqPesq);
	
	// Tentando abrir o arquivo de entrada com os dados
	arq = fopen(NOME_ARQ_FREQ, "rb");
	if(arq == NULL){
		printf("\n\nErro ao tentar ler o arquivo com os dados!\n");
		erroPesquisa=1;
	} else {
		// Pesquisando e filtrando o dados
		while(feof(arq) == 0){
			if(fread(&freqLido, sizeof(Frequentador), 1, arq) == 1){
				// Convertendo o nome lido para minusculo em uma variavel auxiliar
				strcpy(nomeFreqLidoAux, freqLido.nome);
				toLowerStr(nomeFreqLidoAux);
				
				// Comparando o nome lido no arquivo com o pesquisado
				if(strstr(nomeFreqLidoAux, nomeFreqPesq) != NULL){
					// Tentando alocar memoria
					freqAux = realloc(frequentadores, sizeof(Frequentador)*(qtdFreqEncontrados+1));
					if(freqAux != NULL){
						frequentadores = freqAux;
						frequentadores[qtdFreqEncontrados] = freqLido;
						qtdFreqEncontrados++;
					} else {
						printf("\n\nErro de alocacao!\n");
						erroPesquisa=1;
						break;
					}
				}
			}
		}
		fclose(arq);
	}
	
	// Verificando se ocorreu algum erro
	if(erroPesquisa == 1){
		printf("Pesquisa encerrada!");
	} else if(qtdFreqEncontrados == 0){
		printf("\n\nNao foi encontrado nenhum frequentador com esse nome!");
	} else {
		// Ordenando os frequentadores encontrados pelo nome
		ordenaFreqPeloNome(frequentadores, qtdFreqEncontrados);
		
		// Apresentando os dados encontrados
		LIMPA_TELA;
		apresentaDadosAcademia();
		printf("\nFrequentadores encontrados:\n\n");
		apresentaDadosFrequentadoresMemoria(frequentadores, qtdFreqEncontrados);
		free(frequentadores);		
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Ordenar os dados dos frequentadores por ordem alfabetica de nomes usando Qsort
	Parametros: endereco de memoria inicial do vetor de frequentadores, qtd de frequentadores
	Retorno: nenhum
*/
void ordenaFreqPeloNome(Frequentador *frequentadores, int qtdFreq){
	qsort(frequentadores, qtdFreq, sizeof(Frequentador), verificaOrdenacaoNomeFreq);
}

/*
	Objetivo: Verificar se os dados devem ser trocados pela Qsort
	Parametros: dois enderecos de memoria
	Retorno: um valor menor, maior ou igual a zero
*/
int verificaOrdenacaoNomeFreq(const void *p1, const void *p2){
	Frequentador *freq1, *freq2;
	
	freq1 = (Frequentador*) p1;
	freq2 = (Frequentador*) p2;
	
	return strcasecmpLAB(freq1->nome, freq2->nome);
}

void pesqFrequentadoresPelaSerie(void){
	int identificadorSerie, erroPesquisa=0;
	int qtdAtivEncontradas=0, qtdFreqEncontrados=0;
	FILE *arqvFrequentador, *arqvAtividade;
	AtividadeDesenvolvida *atividades=NULL, *atividadesAux, atvdLida;
	Frequentador *frequentadores=NULL, *frequentadoresAux, freqLido;
	int cont;

	apresentaDadosAcademia();
	printf("\n");
	
	// Verificando se existem atividades cadastradas
	if(obtemQtdAtivDesevCadastradas() == 0){
		printf("Nao existem atividades cadastradas!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		return;
	}
	
	// Caso existam series
	apresentaDadosSeriesExsArq();
	
	// Coletando o identifiador da serie a ser pesquisado
	identificadorSerie = leValidaInt("\n\nCod. Identificador da serie: ", "Identificador invalido... Digite novamente: ", VAL_MIN_ID_SERIE, VAL_MAX_ID_SERIE);
	
	if(!existeSerie(identificadorSerie)){
		printf("\nSerie nao encontrada!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		return;
	}
	
	arqvAtividade = fopen(NOME_ARQ_ATIVDESEV, "rb");
	
	if(arqvAtividade == NULL){
		printf("\n\nErro ao tentar ler o arquivo com os dados!\n");
		erroPesquisa=1;
	} else {
		// Pesquisando e filtrando o dados
		while(!feof(arqvAtividade)){
			if(fread(&atvdLida, sizeof(AtividadeDesenvolvida), 1, arqvAtividade) == 1){
				// Comparando o identifiador lido no arquivo com o pesquisado
				if(atvdLida.identificadorSerie == identificadorSerie){
					// Tentando alocar memoria
					atividadesAux = realloc(atividades, sizeof(AtividadeDesenvolvida)*(qtdAtivEncontradas+1));
					
					if(atividadesAux != NULL){
						atividades = atividadesAux;
						atividades[qtdAtivEncontradas] = atvdLida;
						++qtdAtivEncontradas;
					} else{
						printf("\n\nErro de alocacao!\n");
						erroPesquisa=1;
						break;
					}
				}
			}
		}
	
		fclose(arqvAtividade);
	}
	
	// Verificando se ocorreu algum erro
	if(erroPesquisa == 1){
		printf("Pesquisa encerrada!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		
		return;
	} else if(qtdAtivEncontradas == 0){
		printf("\n\nNao foi encontrado nenhuma atividade com esse identifiador!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		
		return;
	}
	
	arqvFrequentador = fopen(NOME_ARQ_FREQ, "rb");
	
	if(arqvFrequentador == NULL){
		printf("\n\nErro ao tentar ler o arquivo com os dados!\n");
		erroPesquisa=1;
	} else {
		// Pesquisando e filtrando o dados
		while(!feof(arqvFrequentador)){
			if(fread(&freqLido, sizeof(Frequentador), 1, arqvFrequentador) == 1){
			
				for(cont=0; cont<qtdAtivEncontradas; ++cont){
					// Comparando o identifiador lido no arquivo com o pesquisado
					if(freqLido.matricula == atividades[cont].matriculaFrequentador){
						// Tentando alocar memoria
						frequentadoresAux = realloc(frequentadores, sizeof(Frequentador)*(qtdFreqEncontrados+1));
					
						if(frequentadoresAux != NULL){
							frequentadores = frequentadoresAux;
							frequentadores[qtdFreqEncontrados] = freqLido;
							++qtdFreqEncontrados;
						} else{
							printf("\n\nErro de alocacao!\n");
							erroPesquisa=1;
						}
						
						break;
					}
				}
				
				if(erroPesquisa == 1){
					break;
				}
			}
		}
	
		fclose(arqvFrequentador);
	}
	
	// Verificando se ocorreu algum erro
	if(erroPesquisa == 1){
		printf("Pesquisa encerrada!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		
		return;
	} else if(qtdFreqEncontrados == 0){
		printf("\n\nNao foi encontrado nenhum frequentador para essa serie!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		
		return;
	}
	
	
	
	// Ordenando os frequentadores encontrados pelo nome
	ordenaFreqPeloNome(frequentadores, qtdFreqEncontrados);
	
	LIMPA_TELA;
	apresentaDadosAcademia();
	
	// apresenta os dados encontrados
	printf("\nFrequentadores encontrados:\n\n");
	
	apresentaDadosFrequentadoresMemoria(frequentadores, qtdFreqEncontrados);
	
	free(atividades);
	free(frequentadores);
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Pesquisar frequentadores que nao utilizam a academia por mais de uma quantidade de dias
	Parametros: nenhum
	Retorno: nenhum
*/
void pesqNaoFrequentaPorQtdDias(void){
	int qtdDias, erroPesquisa=0;
	int qtdAtivEncontradas=0, qtdFreqEncontrados=0;
	FILE *arqvFrequentador, *arqvAtividade;
	AtividadeDesenvolvida *atividades=NULL, *atividadesAux, atvdLida;
	Frequentador *frequentadores=NULL, *frequentadoresAux, freqLido;
	int cont;
	
	apresentaDadosAcademia();
	printf("\n");
	
	// Verificando se existem atividades cadastradas
	if(obtemQtdAtivDesevCadastradas() == 0){
		printf("Nao existem atividades cadastradas!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		return;
	}
	
	qtdDias = leValidaInt("\n\nInforme a qtd de dias: ", "Valor invalido... Digite novamente: ", 1, 5000);
	
	arqvAtividade = fopen(NOME_ARQ_ATIVDESEV, "rb");
	
	if(arqvAtividade == NULL){
		printf("\n\nErro ao tentar ler o arquivo com os dados!\n");
		erroPesquisa=1;
	} else {
		// Pesquisando e filtrando o dados
		while(!feof(arqvAtividade)){
			if(fread(&atvdLida, sizeof(AtividadeDesenvolvida), 1, arqvAtividade) == 1){
				// Comparando o identifiador lido no arquivo com o pesquisado
				if(diferencaDias(atvdLida.dataInicio, obtemDataSistema()) > qtdDias){
					// Tentando alocar memoria
					atividadesAux = realloc(atividades, sizeof(AtividadeDesenvolvida)*(qtdAtivEncontradas+1));
					
					if(atividadesAux != NULL){
						atividades = atividadesAux;
						atividades[qtdAtivEncontradas] = atvdLida;
						++qtdAtivEncontradas;
					} else{
						printf("\n\nErro de alocacao!\n");
						erroPesquisa=1;
						break;
					}
				}
			}
		}
	
		fclose(arqvAtividade);
	}
	
	// Verificando se ocorreu algum erro
	if(erroPesquisa == 1){
		printf("Pesquisa encerrada!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		
		return;
	} else if(qtdAtivEncontradas == 0){
		printf("\n\nNao foi encontrado nenhuma atividade feita a mais de %d dias!", qtdDias);
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		
		return;
	}
	
	arqvFrequentador = fopen(NOME_ARQ_FREQ, "rb");
	
	if(arqvFrequentador == NULL){
		printf("\n\nErro ao tentar ler o arquivo com os dados!\n");
		erroPesquisa=1;
	} else {
		// Pesquisando e filtrando o dados
		while(!feof(arqvFrequentador)){
			if(fread(&freqLido, sizeof(Frequentador), 1, arqvFrequentador) == 1){
			
				for(cont=0; cont<qtdAtivEncontradas; ++cont){
					// Comparando o identifiador lido no arquivo com o pesquisado
					if(freqLido.matricula == atividades[cont].matriculaFrequentador){
						// Tentando alocar memoria
						frequentadoresAux = realloc(frequentadores, sizeof(Frequentador)*(qtdFreqEncontrados+1));
					
						if(frequentadoresAux != NULL){
							frequentadores = frequentadoresAux;
							frequentadores[qtdFreqEncontrados] = freqLido;
							++qtdFreqEncontrados;
						} else{
							printf("\n\nErro de alocacao!\n");
							erroPesquisa=1;
						}
						
						break;
					}
				}
				
				if(erroPesquisa == 1){
					break;
				}
			}
		}
	
		fclose(arqvFrequentador);
	}
	
	// Verificando se ocorreu algum erro
	if(erroPesquisa == 1){
		printf("Pesquisa encerrada!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		
		return;
	} else if(qtdFreqEncontrados == 0){
		printf("\n\nNao foi encontrado nenhum frequentador para essa serie!");
		continuarComEnter("\n\nPressione [Enter] para continuar...");
		
		return;
	}
	
	
	
	// Ordenando os frequentadores encontrados pelo nome
	ordenaFreqPeloNome(frequentadores, qtdFreqEncontrados);
	
	LIMPA_TELA;
	apresentaDadosAcademia();
	
	// apresenta os dados encontrados
	printf("\nFrequentadores encontrados:\n\n");
	
	apresentaDadosFrequentadoresMemoria(frequentadores, qtdFreqEncontrados);
	
	free(atividades);
	free(frequentadores);
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}
