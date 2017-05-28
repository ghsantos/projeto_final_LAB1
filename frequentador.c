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
	Retorno: 0(os dados nao foram recuperador) ou 1(os dados foram recuperados com exito)
*/
int obtemDadosFrequentador(Frequentador *frequentador, int posicaoFreqArq){
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
	Objetivo: Apresentar os dados de todos os frequentadores cadastrados
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaDadosFrequentadores(void){
	FILE *arq;
	Frequentador frequentador;
	int existeFreq=0;
	
	arq = fopen(NOME_ARQ_FREQ, "rb");
	if(arq != NULL){
		printf("%-10.10s%-15.15s%-13.13s%s\n", "Matricula", "Nome", "CPF", "Sexo");
		while(feof(arq) == 0){
			if(fread(&frequentador, sizeof(Frequentador), 1, arq) == 1){
				printf("%-10d%-14.14s %-13.13s", frequentador.matricula, frequentador.nome, frequentador.cpf);
				printf("%s\n", frequentador.sexo == 'M' ? "Masculino" : "Feminino");
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
	Objetivo: Apresentar os dados de um frequentador
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
			printf("CPF invalido! Digite apenas os nros.\n");
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
	int matriculaPesq, posicaoFreqArq;
	
	apresentaDadosAcademia();
	
	// Verificando se tem frequentadores cadastrados
	if(obtemQtdFreqCadastrados() == 0){
		printf("\n\nNao existem frequentadores cadastrados!\n");
	} else {
		printf("\n\n");
		apresentaDadosFrequentadores();
		matriculaPesq = leValidaInt("\n\nMatricula do frequentador a ser alterado: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
		
		// Verificando se a matricula existe
		posicaoFreqArq = obtemPosicaoFreqArq(matriculaPesq);
		if(posicaoFreqArq == 0){
			printf("\n\nNao foi encontrado nenhum frequentador com essa matricula!");
		} else {
			// Obtendo os dados do frequentador selecionado
			if(obtemDadosFrequentador(&frequentador, posicaoFreqArq) == 0){
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
	int dadosModificados=0;
	
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
	int matriculaPesq, posicaoFreqArq;
	char opcaoDesejada;
	
	
	apresentaDadosAcademia();
	
	if(obtemQtdFreqCadastrados() == 0){
		printf("\n\nNao existem frequentadores cadastrados!\n");
	} else {
		printf("\n\n");
		apresentaDadosFrequentadores();
		matriculaPesq = leValidaInt("\n\nMatricula do frequentador a ser excluido: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
		
		// Verificando se a matricula existe
		posicaoFreqArq = obtemPosicaoFreqArq(matriculaPesq);
		if(posicaoFreqArq == 0){
			printf("\n\nNao foi encontrado nenhum frequentador com essa matricula!");
		} else {
			// Obtendo os dados do frequentador selecionado
			if(obtemDadosFrequentador(&frequentador, posicaoFreqArq) == 0){
				printf("\n\nErro ao tentar recuperar os dados do frequentador!");
			} else {
				LIMPA_TELA;
				apresentaDadosAcademia();
				apresentaDadosFrequentador(&frequentador);
				opcaoDesejada = leValidaOpcao("\n\nDeseja excluir esse frequentador[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
				
				if(opcaoDesejada == 'N'){
					printf("\n\nNenhum frequentador foi excluido!");
				} else {
					// Verificando se o frequentador ja executou alguma atividade na academia
					if(verifFreqDevAtividades(frequentador.matricula) == 1){
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
	}
	
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Verificar se um determinado frequentador ja executou alguma serie de exercicios (Atividade desenvolvidas)
	Parametros: matricula do frequentador
	Retorno: 0(nao existem atividades cadastradas) ou 1(ja executou alguma atividade)
*/
int verifFreqDevAtividades(int matriculaVerif){
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
	}
	
	return jaDesenvolveuAtiv;
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
	arqAux = fopen("arqFreqAux.bin", "wb");
	if(arq != NULL){
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
