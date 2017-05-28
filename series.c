#include "series.h"

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
	Objetivo: Obter uma serie de exercicios de um arquivo a partir de um identificador
	Parametros: identificador
	Retorno: a serie de exercicios obtida
*/
SerieExercicio obtemSerie(int identificadorSerie){
	FILE *arqv;
	SerieExercicio serieLida;
	
	arqv = fopen(NOME_ARQ_SERIEEX, "rb");	
	
	if(arqv != NULL){
		while(!feof(arqv)){
			if(fread(&serieLida, sizeof(SerieExercicio), 1, arqv) == 1){
				if(serieLida.identificadorSerie == identificadorSerie){
					break;
				}
			}
		}
		fclose(arqv);
	}
	
	return serieLida;
}

/*
	Objetivo: exibir uma serie de exercicios e o cabecalho se o modo for 1
	Parametros: Uma struct de serie de exercicios e o modo de exibicao
	Retorno: nenhum
*/
void printSerieExercicio(SerieExercicio serie, int modo){

	if(modo == 1){
		printf(" Identificador |             Descricao | Duracao | Qtd calorias a serem perdidas\n");
	}

	printf(" %13d | %21.21s | %7d | %5d\n", serie.identificadorSerie,
		   serie.descricao, serie.duracao, serie.qtdCaloriasPerdidas);
}

/*
	Objetivo: Listar as series de exercicios salvas na memoria
	Parametros: nenhum
	Retorno: nenhum
*/
void listaSerieExercicios(){
	FILE *arqv;
	SerieExercicio serie;
	int cont=0;

	arqv = fopen(NOME_ARQ_SERIEEX, "rb");
	
	if(arqv != NULL){
		
		printf("Series de exercicios\n");
	
		while(!feof(arqv)){
			if(fread(&serie, sizeof(SerieExercicio), 1, arqv) == 1){
				printSerieExercicio(serie, cont+1);
				
				++cont;
			}
		}
		fclose(arqv);
	}
}

/*
	Objetivo: Ler uma serie de exercicios
	Parametros: O endereco de uma struct de serie de exercicios e o modo de leitura
			   ( 1 - ler para uma serie nao cadastrada, 2 - ler para uma serie ja cadastrada)
	Retorno:  1 se a serie foi lida, 0 se nao
*/
int leSerieExercicios(SerieExercicio *serie, int modo){

	serie->identificadorSerie = leValidaInt("\nIdentificador da serie: ", "\nIdentificador invalido\nTente novamente: ", VAL_MIM_ID_SERIE, VAL_MAX_ID_SERIE);
	
	if(existeSerie(serie->identificadorSerie)){
		if(modo == 1){
			return 0;
		}
	} else{
		if(modo == 2){
			return 0;
		}
	}
	
	leValidaTexto("Descricao: ", "Descricao invalida\nTente novamente: ", serie->descricao, TAM_MIN_DESCRICAO_SERIE, TAM_DESCRICAO_SERIE);

	serie->duracao = leValidaInt("Duracao (minutos): ", "Valor invalido\nTente novamente: ", VAL_MIM_DURACAO_SERIE, VAL_MAX_DURACAO_SERIE);
	
	serie->qtdCaloriasPerdidas = leValidaInt("Quantidade de calorias a serem perdidas: ", "Quantidade invalida\nTente novamente: ", VAL_MIM_CAL_PERDIDAS, VAL_MAX_CAL_PERDIDAS);
	
	return 1;
}

/*
	Objetivo: Cadastrar uma nova serie de exercicios
	Parametros: nenhum
	Retorno: nenhum
*/
void cadastraNovaSerie(){

	FILE *arqv;
	SerieExercicio serie;
	
	// A serie de exercicios ja existe
	if(!leSerieExercicios(&serie, 1)){
		printf("Serie ja cadastrada\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}
	
	if(verificaArqExiste(NOME_ARQ_SERIEEX)){
		arqv = fopen(NOME_ARQ_SERIEEX, "ab+");
	} else{
		arqv = fopen(NOME_ARQ_SERIEEX, "wb+");
	}
	
	if(arqv != NULL){
		if(fwrite(&serie, sizeof(SerieExercicio), 1, arqv) == 1){
			printf("\n\nSerie cadastrada com sucesso!");
		} else {
			printf("\n\nErro ao tentar cadastrar Serie !");
		}
	
		continuarComEnter("\nPressione [Enter] para continuar...\n");
	
		fclose(arqv);
	}

}

/*
	Objetivo: obter a quantidade de series salvas na memoria
	Parametros: nenhum
	Retorno: quantidade de series salvas na memoria
*/
int obtemQtdSeriesCadastradas(){
	FILE *arq;
	int qtdAtividades=0;
	
	arq = fopen(NOME_ARQ_ATIVDESEV, "rb");
	if(arq != NULL){
		if(fseek(arq, 0, SEEK_END) == 0){
			qtdAtividades = ftell(arq) / sizeof(SerieExercicio);
		}
		fclose(arq);
	}
	
	return qtdAtividades;
}

/*
	Objetivo: Alterar dados de uma serie de exercicios
	Parametros: nenhum
	Retorno: nenhum
*/
void alteraDadosSeries(){
	SerieExercicio serie, serieLida;
	FILE *arqv;
	char continuar;
	
	if(obtemQtdSeriesCadastradas() == 0){
		printf("Nenhuma serie de exercicio cadastrada\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}

	listaSerieExercicios();

	if(!leSerieExercicios(&serie, 2)){
		printf("Identificador inexistente\n");
	
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}
	
	LIMPA_TELA;
	
	printSerieExercicio(serie, 1);
	
	continuar = leValidaOpcao("\nConfirmar alteracao (S/n)? ", "Opcao invalida\nTente novamente: ", "SN");
	
	if(continuar == 'N'){
		return;
	}
	
	arqv = fopen(NOME_ARQ_SERIEEX, "rb+");
	
	if(arqv != NULL){
		fseek(arqv, 0, SEEK_SET);
	
		while(!feof(arqv)){
			if(fread(&serieLida, sizeof(SerieExercicio), 1, arqv) != 1){
				
				printf("Erro na alteracao de dados\n");
				
				fclose(arqv);
				
				continuarComEnter("\nPressione [Enter] para continuar...\n");
				
				return;
			}
		
			if(serie.identificadorSerie == serieLida.identificadorSerie){
				break;
			}
		}
		
		if(fseek(arqv, -(sizeof(SerieExercicio)), SEEK_CUR) != 0){
			printf("Erro na alteracao de dados\n");
				
			fclose(arqv);
			
			continuarComEnter("\nPressione [Enter] para continuar...\n");
				
			return;
		}
		
		fwrite(&serie, sizeof(SerieExercicio), 1, arqv);
		
		fclose(arqv);
		
		printf("\n\nSerie alterada com sucesso!");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
	}
	
	

}

/*
	Objetivo: Excluir uma serie de exercicios
	Parametros: nenhum
	Retorno: nenhum
*/
void excluirSeries(){
	SerieExercicio serie, serieLida;
	FILE *arqv, *arqvAux;
	char continuar;
	int identificador;
	
	if(obtemQtdSeriesCadastradas() == 0){
		printf("Nenhuma serie de exercicio cadastrada\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}

	listaSerieExercicios();
	
	identificador = leValidaInt("\nIdentificador da serie: ", "\nIdentificador invalido\nTente novamente: ", VAL_MIM_ID_SERIE, VAL_MAX_ID_SERIE);

	if(!existeSerie(identificador)){
		printf("Identificador inexistente\n");
	
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;
	}
	
	serie = obtemSerie(identificador);

	LIMPA_TELA;
	
	printSerieExercicio(serie, 1);
	
	continuar = leValidaOpcao("\nConfirmar exclusao (S/n)? ", "Opcao invalida\nTente novamente: ", "SN");
	
	if(continuar == 'N'){
		return;
	}
	
	arqv = fopen(NOME_ARQ_SERIEEX, "rb");
	arqvAux = fopen("arqv_aux.bin", "wb");
	
	if(arqv == NULL || arqvAux == NULL){
		printf("Erro ao abrir arquivos\n");
		
		continuarComEnter("\nPressione [Enter] para continuar...\n");
		
		return;		
	}

	while(!feof(arqv)){
		if(fread(&serieLida, sizeof(SerieExercicio), 1, arqv) == 1){
			if(serieLida.identificadorSerie != serie.identificadorSerie){
				if(fwrite(&serieLida, sizeof(SerieExercicio), 1, arqvAux) != 1){
					printf("\nErro na exclusao de dados\n");
					
					continuarComEnter("\nPressione [Enter] para continuar...\n");
				
					fclose(arqv);
	
					fclose(arqvAux);
				
					return;
				}
			}
		} else{
			break;
			
		}
	}
	
	fclose(arqv);
	
	fclose(arqvAux);
	
	remove(NOME_ARQ_SERIEEX);

	rename("arqv_aux.bin", NOME_ARQ_SERIEEX);
	
	printf("\n\nSerie excluida com sucesso!");

	continuarComEnter("\nPressione [Enter] para continuar...\n");

}
