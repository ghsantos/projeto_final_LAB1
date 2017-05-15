#ifndef FUNC_ESTRUTURAS_H
#define FUNC_ESTRUTURAS_H

#include <time.h>
#include "estruturas.h"

/*
    Objetivo: obter a data atual do sistema
    Parâmetros: nenhum
    retorno: Uma struct com a data atual do sistema
*/
Data dataSistema(){
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
    Objetivo: obter a hora atual do sistema
    Parâmetros: nenhum
    retorno: Uma struct com a hora atual do sistema
*/
Horario horaSistema(){
	Horario horario;
	
	struct tm *local;
	time_t t = time(NULL);
	
	local = localtime(&t);
	
	horario.minuto = local->tm_min;
	horario.hora = local->tm_hour;
	
	return horario;
}

#endif  // #ifndef FUNC_ESTRUTURAS_H
