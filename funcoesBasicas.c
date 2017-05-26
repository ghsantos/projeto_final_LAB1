#include "definicoes.h"
#include "estruturas.h"
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
	Objetivo: Verificar se um nro de CPF e valido
	Parametros: endereco de memoria da string com o CPF
	Retorno: 0(invalido) ou 1(valido)
*/
int verifCPFValido(char *cpf){
	int cont;
	
	// Verificando se foi digitado apenas nros
	for(cont=0; cont<strlen(cpf); cont++){
		if(!isdigit(cpf[cont])){
			return 0;
		}
	}
	
	return 1;
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
	
	printf("Z - Encerrar o programa\n\n");
}
