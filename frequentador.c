#include "definicoes.h"
#include "estruturas.h"
#include "funcoesBasicas.h"
#include "frequentador.h"

/*
	Objetivo: Cadastrar um frequentador gravando os seus dados em um arquivo de saida
	Parametros: nenhum
	Retorno: nenhum
*/
void cadastraFrequentador(void){
	Frequentador frequentador;
	int cpfValido;
	
	
	printf("CADASTRAR FREQUENTADOR\n\n");
	
	// Gerando uma matricula aleatorio (unica)
	do{
		frequentador.matricula = geraNroIntAleatorio(VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
	}while(obtemPosicaoFreqArq(frequentador.matricula) != 0);
	printf("Matricula gerada: %d\n", frequentador.matricula);
	
	// Obtendo o nome
	leValidaTexto("\nNome completo: ", "Nome invalido... Digite no minimo 3 caracteres: ", frequentador.nome, TAM_MIN_NOME_FREQ, TAM_MAX_NOME_FREQ);
	
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
	if(gravaDadosFreqArq(&frequentador) == 0){
		printf("\n\nErro ao tentar cadastrar o frequentador!");
	} else {
		printf("\n\nFrequentador cadastrado com sucesso!");
	}
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
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
	Objetivo: Gravar os dados de um frequentador em um arquivo
	Parametros: endereco de memoria da struct com os dados do frequentador
	Retorno: 0(erro no cadastro) ou 1(cadastro concluido)
*/
int gravaDadosFreqArq(Frequentador *frequentador){
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
	Objetivo: Alterar os dados de um frequentador (com excecao da matricula)
	Parametros: nenhum
	Retorno: nenhum
*/
void alteraDadosFrequentador(void){
	Frequentador frequentador;
	int matriculaPesq, posicaoFreqArq, cpfValido;
	char opcaoAlteracao;
	
	printf("ALTERAR DADOS DO FREQUENTADOR\n\n");
	apresentaDadosFrequentadores();
	
	// Obtendo a matricula do funcionario a ser alterado
	matriculaPesq = leValidaInt("\n\nMatricula do frequentador a ser alterado: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
	// Obtendo (caso exista) a posicao dos dados do frequentador da matricula coletada dentro do arquivo de entrada
	posicaoFreqArq = obtemPosicaoFreqArq(matriculaPesq);
	
	// Verificando se foi encontrada a posicao com os dados
	if(posicaoFreqArq == 0){
		printf("\n\nNenhum frequentador com essa matricula foi encontrado!\n");
	}  else {
		// Obtendo todos os dados do frequentador 'marcado' para alteracao
		if(obtemDadosFrequentadorArq(&frequentador, posicaoFreqArq) == 0){
			printf("\n\nErro ao tentar recuperar os dados desse frequentador no arquivo!\n");
		} else {
			apresentaDadosFrequentador(&frequentador);
			opcaoAlteracao = leValidaOpcao("\nDeseja alterar esses dados[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
			
			// Verificando se o usuario deseja realmente alterar o tal frequentador
			if(opcaoAlteracao == 'N'){
				printf("\n\nNenhum dado foi modificado!\n");
			} else {
				opcaoAlteracao = leValidaOpcao("\nAlterar = \n[N]-Nome ou [C]-CPF ou [P]-Peso ou [S]-Sexo ou [D]-Data de ingresso: ", "Opcao invalida... Digite novamente: ", "NCPSD");
				switch(opcaoAlteracao){
					case 'N': // Altera nome
						leValidaTexto("\nNovo Nome: ", "Nome invalido... Digite no minimo 3 caracteres: ", frequentador.nome, TAM_MIN_NOME_FREQ, TAM_MAX_NOME_FREQ);
						break;
					
					case 'C':
						do{
							leValidaTexto("\nNovo CPF (apenas nros): ", "CPF invalido... Digite os 11 digitos: ", frequentador.cpf, (TAM_CPF-1), TAM_CPF);
							cpfValido = verifCPFValido(frequentador.cpf);
							
							if(cpfValido == 0){
								printf("CPF invalido! Digite apenas os nros.\n");
							}
						}while(cpfValido == 0);
						break;
						
					case 'P':
						frequentador.peso = leValidaFloat("\nNovo Peso (Kg): ", "Peso invalido... Digite novamente: ", VAL_MIN_PESO, VAL_MAX_PESO);
						break;
						
					case 'S':
						frequentador.sexo = leValidaOpcao("\nNovo Sexo[M/f]: ", "Sexo invalido... Digite apenas M ou F: ", "MF");
						break;
						
					case 'D':
						frequentador.dataIngresso = obtemDataSistema();
						printf("\nUma nova data de ingresso foi obtida!");
						break;
				}
				
				// Tentando gravar os novos dados do frequentador no arquivo de saida
				if(gravaDadosFreqAlterados(&frequentador, posicaoFreqArq) == 0){
					printf("\n\nErro ao tentar alterar os dados!\n");
				} else {
					printf("\n\nDados alterados com sucesso!\n");
				}
			}
		}
	}
	
	
	continuarComEnter("\n\nPressione [Enter] para continuar...");
}

/*
	Objetivo: Gravar os dados alterados de um frequentador no arquivo de saida
	Parametros: endereco de memoria da struct com os dados, posicao do frequentador no arquivo
	Retorno: 0(erro na gravacao) ou 1(gravacao concluida)
*/
int gravaDadosFreqAlterados(Frequentador *frequentador, int posicaoFreqArq){
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
	Objetivo: Obter os dados de um frequentador a partir da sua posicao dentro de um arquivo de entrada
	Parametros: endereco de memoria da struct(frequentador) que vai armazenar os dados, posicao dos dados
		do frequentador no arquivo
	Retorno: 0(os dados nao foram recuperador) ou 1(os dados foram recuperados com exito)
*/
int obtemDadosFrequentadorArq(Frequentador *frequentador, int posicaoFreqArq){
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
	Objetivo: Excluir um frequentador
	Parametros: nenhum
	Retorno: nenhum
*/
void excluiFrequentador(void){
	Frequentador frequentador;
	int matriculaPesq, posicaoFreqArq;
	char desejaExcluir;
	
	printf("EXCLUIR FREQUENTADOR\n\n");
	apresentaDadosFrequentadores();
	
	// Coletando a matricula do frequentador a ser excluido
	matriculaPesq = leValidaInt("\n\nMatricula do frequentador a ser excluido: ", "Matricula invalida... Digite novamente: ", VAL_MIN_MATRIC_FREQ, VAL_MAX_MATRIC_FREQ);
	// Verificando se o frequentador com tal matricula existe no arquivo de entrada
	posicaoFreqArq = obtemPosicaoFreqArq(matriculaPesq);
	
	if(posicaoFreqArq == 0){
		printf("\n\nNenhum frequentador com essa matricula foi encontrado!\n");
	}  else {
		// Obtendo todos os dados do frequentador em questao ('marcado')
		if(obtemDadosFrequentadorArq(&frequentador, posicaoFreqArq) == 0){
			printf("\n\nErro ao tentar recuperar os dados desse frequentador no arquivo!\n");
		} else {
			apresentaDadosFrequentador(&frequentador);
			desejaExcluir = leValidaOpcao("\nDeseja excluir esse frequentador[S/n]: ", "Opcao invalida... Digite apenas S ou N: ", "SN");
			
			// Verificando se o usuario quer realmente excluir o frequentador marcado
			if(desejaExcluir == 'N'){
				printf("\n\nNenhum frequentador foi excluido!\n");
			} else {
				// Verificando se o frequentador ja executou ao menos uma atividade na academia
				if(verifFreqDevAtividades(frequentador.matricula) == 1){
					printf("\n\nErro ao tentar excluir o frequentador!\nEste frequentador ja desenvolveu alguma serie de exercicios!\n");
				} else {
					// Removendo os dados do frequentador
					if(removeFreqArq(frequentador.matricula) == 0){
						printf("\n\nErro ao tentar excluir o frequentador!\n");
					} else {
						printf("\n\nFrequentador excluido com sucesso!\n");
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
int removeFreqArq(int matriculaFreqExc){
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
