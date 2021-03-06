#include "funcoesBasicas.h"


/*
	Objetivo: Ler e validar um nro inteiro
	Parametros: endereco de memoria da string mensagem e mensagem de erro,
		valor minimo e maximo permitido
	Retorno: nro inteiro valido
*/
int leValidaInt(char *msg, char *msgErro, int valMin, int valMax){
	int nro, resultValidScanf;
	
	printf("%s", msg);
	do{
		do{
			LIMPA_BUFFER;
			resultValidScanf = scanf("%d", &nro);
			LIMPA_BUFFER;
			
			if(resultValidScanf == 0){
				printf("Erro ao ler o nro... Digite novamente: ");
			}
		}while(resultValidScanf == 0);
		
		if(nro < valMin || nro > valMax){
			printf("%s",msgErro);
		}
	}while(nro < valMin || nro > valMax);
	
	return nro;
}

/*
	Objetivo: Ler e validar um nro real
	Parametros: endereco de memoria da string mensagem e mensagem de erro,
		valor minimo e maximo permitido
	Retorno: nro real valido
*/
float leValidaFloat(char *msg, char *msgErro, float valMin, float valMax){
	float nro;
	int resultValidScanf;
	
	printf("%s",msg);
	do{
		do{
			LIMPA_BUFFER;
			resultValidScanf = scanf("%f", &nro);
			LIMPA_BUFFER;
			
			if(resultValidScanf == 0){
				printf("Erro ao ler o nro... Digite novamente: ");
			}
		}while(resultValidScanf == 0);
		
		if(nro < valMin || nro > valMax){
			printf("%s",msgErro);
		}
	}while(nro < valMin || nro > valMax);
	
	return nro;
}

/*
	Objetivo: Ler e validar um texto
	Parametros: endereco de memoria da string mensagem, mensagem de erro e do texto,
		qtd minima e maxima de caracteres a serem permitidos
	Retorno: nenhum
*/
void leValidaTexto(char *msg, char *msgErro, char *texto, int tamTexto){
	printf("%s",msg);
	do{
		LIMPA_BUFFER;
		fgets(texto, tamTexto, stdin);
		LIMPA_BUFFER;
		tiraTerminador(texto);
		
		if(strlen(texto) == 0){
			printf("%s",msgErro);
		}
	}while(strlen(texto) == 0);
}

/*
	Objetivo: Tirar o \n de uma string
	Parametros: endereco de memoria da string texto
	Retorno: nenhum
*/
void tiraTerminador(char *texto){
	if(texto[strlen(texto)-1] == '\n'){
		texto[strlen(texto)-1] = '\0';
	}
}

/*
	Objetivo: Ler e validar uma opcao
	Parametros: endereco de memoria da string mensagem, mensagem de erro e das opcoes validas
	Retorno: opcao valida
*/
char leValidaOpcao(char *msg, char *msgErro, char *opcoesValidas){
	char opcao;
	
	printf("%s",msg);
	do{
		LIMPA_BUFFER;
		opcao = toupper(getchar());
		LIMPA_BUFFER;
		
		if(strchr(opcoesValidas, opcao) == NULL){
			printf("%s",msgErro);
		}
	}while(strchr(opcoesValidas, opcao) == NULL);
	
	return opcao;
}

/*
	Objetivo: Ler e validar uma data
	Parametros: endereco de memoria da string mensagem
	Retorno: a data validada
*/
Data leValidaData(char *msg){
	int dataValida;
	Data data;

	do{
		printf("\n%s\n", msg);
		data.dia = leValidaInt("Dia: ", "Dia invalido... Digite novamente: ", 1, 31);
		data.mes = leValidaInt("\nMes: ", "Mes invalido... Digite novamente: ", 1, 12);
		data.ano = leValidaInt("\nAno: ", "Ano invalido... Digite novamente: ", 1901, 2037);
		dataValida = verifDataValida(data);
		
		if(dataValida == 0){
			printf("\nData invalida... Digite novamente!");
		}
	}while(dataValida == 0);
	
	return data;
}

/*
	Objetivo: Validar um CPF
	Parametros: endereco de memoria inicial da string CPF
	Retorno: 0(CPF invalido) ou 1(CPF valido)
*/
int verifCPFValido(char *cpf){
	int cpfInt[11];
	int soma=0, digVerif[2], cont, contAux;
	
	// Lista dos cpfs invalidos mais comuns
	char *cpfInval[] = {"11111111111", "22222222222", "33333333333",
                         "44444444444", "55555555555", "66666666666",
                         "77777777777", "88888888888", "99999999999"};
    
    
    // Verificando se o tamanho do CPF e valido
    if(strlen(cpf) != 11){
    	return 0;
	}
	
	// Verificando se o CPF so tem nros iguais
	for(cont=0; cont<9; cont++){
		if(strcmp(cpfInval[cont], cpf) == 0){
			return 0;
		}
	}
	
	// Transformando os caracteres do CPF em nros
	for(cont=0; cont<strlen(cpf); cont++){
		cpfInt[cont] = cpf[cont] - '0';
	}
	
	// Obtendo o primeiro digito verificador
	contAux=10;
	for(cont=0;cont<9;cont++,contAux--){
		soma += cpfInt[cont] * contAux;
	}
	digVerif[0]=soma % 11;
	digVerif[0]= digVerif[0]<2 ? 0 : 11-digVerif[0];
	
	// Obtendo o segundo digito verificador
	soma=0;
	contAux=11;
	for(cont=0;cont<10;cont++,contAux--){
		if(cont==9){
			soma += digVerif[0] * contAux;
		} else {
			soma+= cpfInt[cont] * contAux;
		}
	}
	digVerif[1]=soma % 11;
	digVerif[1]= digVerif[1]<2 ? 0 : 11-digVerif[1];
	
		
	// Verificando se os digitos verificadores sao validos
	if(digVerif[0] == cpfInt[9] && digVerif[1] == cpfInt[10]){
		// CPF valido
		return 1;
	} else {
		// CPF invalido
		return 0;
	}
}

/*
	Objetivo: Verificar se uma data e valida
	Parametros: dia, mes e ano
	Retorno: 0(data invalida) ou 1(data valida)
*/
int verifDataValida(Data dataVerif){
	Data dataAux = obtemDataSistema();
	int dataValida=1;
	
	// Vericando se o dia, mes e ano esta nos intervalos numericos basicos de datas
    if(dataVerif.ano<0 || dataVerif.ano > dataAux.ano || dataVerif.mes<1 || dataVerif.mes >12 || dataVerif.dia >31){
    	return 0;
	}
	
	// Verificando se a data informada e maior que a data do sistema
	if(dataVerif.ano == dataAux.ano){
		if(dataVerif.mes > dataAux.mes){
			return 0;
		} else if(dataVerif.mes == dataAux.mes && dataVerif.dia > dataAux.dia){
			return 0;
		}
	}
    
    switch(dataVerif.mes){
       // Verificando os meses de 30 dias
	   case 4:
       case 6:
       case 9:
       case 11:
            if(dataVerif.dia > 30){
            	dataValida=0;
			}
            break;
            
       case 2:
       		// Verificando a validade dos anos bissextos
            if((dataVerif.ano%4 == 0 && dataVerif.ano %100 !=0) ||(dataVerif.ano % 400 == 0)){
            	if(dataVerif.dia >29){
               		dataValida = 0;
				}
				
            } else {
            	if(dataVerif.dia >28){
            		dataValida =0;
				}  
            }
            break;      
    }
    
    return dataValida;
}

/*
	Objetivo: Conveter os caracteres de uma string para minusculo
	Parametros: endereco de memoria da string a ser modificada
	Retorno: nenhum
*/
void toLowerStr(char *str){
	int cont;
	
	for(cont=0; cont<strlen(str); cont++){
		str[cont] = tolower(str[cont]);
	}
}

/*
	Objetivo: Conveter os caracteres de uma string para maiusculo
	Parametros: endereco de memoria da string a ser modificada
	Retorno: nenhum
*/
void toUpperStr(char *str){
	int cont;
	
	for(cont=0; cont<strlen(str); cont++){
		str[cont] = toupper(str[cont]);
	}
}

/*
	Objetivo: Gerar um nro inteiro aleatorio
	Parametros: valor minimo e maximo permitido
	Retorno: nro aleatorio
*/
int geraNroIntAleatorio(int valMin, int valMax){
	int nro;
	
	// Semeando/Definindo um valor inicial para a geracao de um nro
	// aleatorios
	srand((unsigned)time(NULL));
	nro = valMin + (rand() % valMax);
	
	return nro;
}

/*
	Objetivo: Obter a data atual do sistema
	Parametros: nenhum
	Retorno: uma struct com a data atual do sistema
*/
Data obtemDataSistema(void){
	Data data;

	struct tm *local;
	time_t t = time(NULL);
	
	local = localtime(&t);
	
	data.dia = local->tm_mday;
	data.mes = local->tm_mon+1;
	data.ano = local->tm_year+1900;
	
	return data;
}

/*
	Objetivo: Obter a hora atual do sistema
	Parametros: nenhum
	Retorno: uma struct com a hora atual do sistema
*/
Horario obtemHoraSistema(void){
	Horario horario;
	
	struct tm *local;
	time_t t = time(NULL);
	
	local = localtime(&t);
	
	horario.minutos = local->tm_min;
	horario.hora = local->tm_hour;
	
	return horario;
}

/*
	Objetivo: obter a diferenca em dias entre duas datas
	Parametros: duas structs do tipo Data
	Retorno: a diferenca em dias entre as datas
*/
int diferencaDias(Data dataInicial, Data dataFinal){
	int dias=0, mesMaior=0, diaMaior=0, diasAMais=0;
	
	// soma a qtd de dias de cada ano
	for(; dataInicial.ano < dataFinal.ano; ++dataInicial.ano){
		
		if((dataInicial.ano % 4 == 0 && dataInicial.ano % 100 != 0) || (dataInicial.ano % 400 == 0)){
			dias += 366;
		} else{
			dias += 365;
		}
	}
	
	// verifica se o mes final e menor que o mes inicial
	if(dataFinal.mes < dataInicial.mes){
		if((dataInicial.ano % 4 == 0 && dataInicial.ano % 100 != 0) || (dataInicial.ano % 400 == 0)){
			dias -= 366;
		} else{
			dias -= 365;
		}
		
		mesMaior = 1;
	}
	
	// o mes final e menor que o mes inicial entao soma-se os dias ate o mes 12
	if(mesMaior == 1){
		for(; dataInicial.mes <= 12; ++dataInicial.mes){
			switch (dataInicial.mes){
				case 2:
					if((dataInicial.ano % 4 == 0 && dataInicial.ano % 100 != 0) || (dataInicial.ano % 400 == 0)){
						dias += 29;
					} else{
						dias += 28;
					}
					break;
			
				case 4:
				case 6:
				case 9:
				case 11:
					dias += 30;
					break;
			
				default:
					dias += 31;
					break;
			}
		}
	
		// atribui 1 para somar os dias dos meses restantes
		dataInicial.mes = 1;
	}
	
	// soma a qtd de dias de cada mes
	for(; dataInicial.mes < dataFinal.mes; ++dataInicial.mes){
		switch (dataInicial.mes){
			case 2:
				if((dataInicial.ano % 4 == 0 && dataInicial.ano % 100 != 0) || (dataInicial.ano % 400 == 0)){
					dias += 29;
				} else{
					dias += 28;
				}
				break;
			
			case 4:
			case 6:
			case 9:
			case 11:
				dias += 30;
				break;
			
			default:
				dias += 31;
				break;
		}
	}

	// verifica se o dia final e menor que o dia inicial
	if(dataFinal.dia < dataInicial.dia){
		switch (dataInicial.mes){
			case 2:
				if((dataInicial.ano % 4 == 0 && dataInicial.ano % 100 != 0) || (dataInicial.ano % 400 == 0)){
					dias -= 29;
					diasAMais = 29;
				} else{
					dias -= 28;
					diasAMais = 28;
				}
				break;
			
			case 4:
			case 6:
			case 9:
			case 11:
				dias -= 30;
				diasAMais = 30;
				break;
			
			default:
				dias -= 31;
				diasAMais = 31;
				break;
		}
		
		diaMaior = 1;
	}
	
	if(diaMaior == 1){
		dias += diasAMais - dataInicial.dia;
		
		// atribui 0 para somar os dias restantes
		dataInicial.dia = 0;
	}
	
	dias += dataFinal.dia - dataInicial.dia;
	
	return dias;
}

/*
	Objetivo: Verificar se uma data esta em um determinado intervalo
	Parametros: a struct da dataInicial, da dataFinal e dataIntervalo
	Retorno: 1 a data esta no intervalo ou 0 caso contrario
*/
int verificaIntervaloDatas(Data dataInicial, Data dataFinal, Data dataIntervalo){
	int datIni=0, datFin=0, datIntervalo=0;

	datIni = dataInicial.ano * 10000;
	datIni += dataInicial.mes * 100;
	datIni += dataInicial.dia;
	
 	datFin = dataFinal.ano * 10000;
	datFin += dataFinal.mes * 100;
	datFin += dataFinal.dia;
	
	datIntervalo = dataIntervalo.ano * 10000;
	datIntervalo += dataIntervalo.mes * 100;
	datIntervalo += dataIntervalo.dia;
	
	if(datIni <= datIntervalo && datIntervalo <= datFin){
		return 1;
	} else{
		return 0;
	}
}

/*
	Objetivo: Verificar se um arquivo existe
	Parametros: endereco de memoria da string com o nome do arquivo
	Retorno: 0(nao existe) ou 1(existe)
*/
int verificaArqExiste(char *nomeArq){
	FILE *arq;
	
	arq = fopen(nomeArq, "r");
	if(arq == NULL){
		return 0;
	} else {
	
		fclose(arq);
	
		return 1;
	}
}

/*
	Objetivo: Pausar a execucao do programa ate o usuario digitar enter
	Parametros: endereco de memoria da string com a mensagem a ser exibida
	Retorno: nenhum
*/
void continuarComEnter(char *msg){
	printf("%s", msg);
	
	LIMPA_BUFFER;
	getchar();
	LIMPA_BUFFER;
}

/*
	Objetivo: Apresentar as opcoes do menu principal
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaOpcoesMenuPrincipal(void){
	printf("\nFrequentador\n");
	printf("A - Cadastrar novo\n");
	printf("B - Alterar dados\n");
	printf("C - Excluir\n\n");
	
	printf("Serie de Exercicio\n");
	printf("D - Cadastrar nova\n");
	printf("E - Alterar dados\n");
	printf("F - Excluir\n\n");
	
	printf("Atividades desenvolvidas\n");
	printf("G - Cadastrar nova\n");
	printf("H - Excluir\n\n");
	
	printf("I - Gerar relatorios\n\n");
	
	printf("Z - Encerrar o programa\n\n");
}

/*
	Objetivo: Apresentar as opcoes do menu de relatorios
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaOpcoesMenuRelatorios(void){
	printf("\nRelatorios disponiveis\n\n");
	printf("A - Pesquisar dados pela chave primaria (R1)\n");
	printf("B - Exibir todos os cadastros do sistema (R1)\n");
	printf("C - Pesquisar frequentadores pelo nome (R2)\n");
	printf("D - Pesquisar frequentador por serie realizada (R3)\n");
	printf("E - Filtrar atividades dos frequentadores por datas (R4)\n");
	printf("F - Listar frequentadores por uma faixa de tempo (R5)\n");
	printf("G - Pesquisar frequentadores que nao frequentam a uma qtd de dias (R6)\n");
	printf("Z - Retornar ao menu principal\n\n");
}
