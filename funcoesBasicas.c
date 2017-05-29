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
	Objetivo: Ler um texto(string) utilizando alocacao dinamica
	Parametros: nenhum
	Retorno: endereco de memoria inicial do vetor de caracteres (string)
*/
char* leString(void){
	char *texto=NULL, *textoAux;
	char caractere;
	int qtdCaracteres=0;
	
	LIMPA_BUFFER;
	do{
		caractere = getchar();
		
		textoAux = (char*) realloc(texto, sizeof(char)*(qtdCaracteres+1));
		if(textoAux != NULL){
			texto = textoAux;
			
			if(caractere != '\n'){
				texto[qtdCaracteres] = caractere;
			} else {
				texto[qtdCaracteres] = '\0';
			}
			qtdCaracteres++;
		} else {
			break;
		}
		
	}while(caractere != '\n');
	
	return texto;
}

/*
	Objetivo: Ler e validar um texto
	Parametros: endereco de memoria da string mensagem, mensagem de erro e do texto,
		qtd minima e maxima de caracteres a serem permitidos
	Retorno: nenhum
*/
void leValidaTexto(char *msg, char *msgErro, char *texto, int tamMinTexto, int tamMaxTexto){
	printf("%s",msg);
	do{
		LIMPA_BUFFER;
		fgets(texto, tamMaxTexto, stdin);
		LIMPA_BUFFER;
		tiraTerminador(texto);
		
		if(strlen(texto) < tamMinTexto){
			printf("%s",msgErro);
		}
	}while(strlen(texto) < tamMinTexto);
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
	Objetivo: verificar a existencia de uma substring em uma string ignorando case
	Parâmetros: o endereco de uma string e de uma substring
 	retorno: 1 caso a substring exista na string ou 0, caso nao
*/
int strcasestrLAB(const char *texto, const char *pesqsa){
	int existe=0, cont;

	char *str, *find;
	
	str = (char *) malloc(sizeof(char) * strlen(texto));
	
	if(str != NULL){
		find = (char *) malloc(sizeof(char) * strlen(pesqsa));

		if(find != NULL){
			for(cont=0; cont < strlen(texto); ++cont){
				str[cont] = toupper(texto[cont]);
			}

			str[cont] = '\0';

			for(cont=0; cont < strlen(pesqsa); ++cont){
				find[cont] = toupper(pesqsa[cont]);
			}

			find[cont] = '\0';

			if(strstr(str, find) != NULL){
				existe = 1;
			}
		
			free(find);
		}
		
		free(str);
	}

	return existe;
}

/*
	Objetivo: comparar duas strings ignorando case
	Parâmetros: o endereco de duas strings
 	retorno: o valor da diferenca entre as strings
*/
int strcasecmpLAB(const char *texto1, const char *texto2){
	int comparacao=0, cont;

	char *str1, *str2;
	
	str1 = (char *) malloc(sizeof(char) * strlen(texto1));
	
	if(str1 != NULL){
		str2 = (char *) malloc(sizeof(char) * strlen(texto2));

		if(str2 != NULL){
			for(cont=0; cont < strlen(texto1); ++cont){
				str1[cont] = toupper(texto1[cont]);
			}

			str1[cont] = '\0';

			for(cont=0; cont < strlen(texto2); ++cont){
				str2[cont] = toupper(texto2[cont]);
			}

			str2[cont] = '\0';

			comparacao = strcmp(str1, str2);
		
			free(str2);
		}
		
		free(str1);
	}

	return comparacao;
}

/*
	Objetivo: Gerar um nro inteiro aleatorio
	Parametros: valor minimo e maximo permitido
	Retorno: nro aleatorio
*/
int geraNroIntAleatorio(int valMin, int valMax){
	int nro;
	
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
	int dias=0;
	
	dias += (dataFinal.ano - dataInicial.ano) * 365;
	
	if(dataFinal.mes < dataInicial.mes){
		dias -= 365;
	}
	
	dias += (dataFinal.mes - dataInicial.mes) * 30;
	
	if(dataFinal.dia < dataInicial.dia){
		dias -= 30;
	}
	
	dias += dataFinal.dia - dataInicial.dia;
	
	return dias;
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
	Objetivo: Apresentar as opcoes do menu
	Parametros: nenhum
	Retorno: nenhum
*/
void apresentaOpcoesMenu(void){
	printf("\nFrequentador\n");
	printf("A - Cadastrar novo\n");
	printf("B - Alterar dados\n");
	printf("C - Excluir\n\n");
	
	printf("Serie de Exercicios\n");
	printf("D - Cadastrar nova\n");
	printf("E - Alterar dados\n");
	printf("F - Excluir\n\n");
	
	printf("Atividades desenvolvidas\n");
	printf("G - Cadastrar nova\n");
	printf("H - Excluir\n\n");
	
	printf("I - Gerar relatorios\n\n");
	
	printf("Z - Encerrar o programa\n\n");
}
