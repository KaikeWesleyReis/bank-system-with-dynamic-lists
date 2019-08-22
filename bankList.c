#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "bankList.h"

//FUNCTIONS - GENERAL USE
void GERAR_LISTA_AG(pont_lista_ag lista_ag){//GENERATE AGENCY LIST - FIRST LEVEL OF ABSTRACTION 	
	lista_ag->prim_ag = (pointerAgencia)malloc(sizeof(celulaAgencia));
	lista_ag->ult_ag = lista_ag->prim_ag;	
	lista_ag->prim_ag->prox_ag = NULL;
}
void GERAR_LISTA_CL(pont_lista_cl lista_cl){//GENERATE A LIST OF CLIENTS FOR EACH CREATED AGENCY - SECOND LEVEL OF ABSTRACTION 
	lista_cl->prim_cl = (pointerCliente)malloc(sizeof(celulaCliente));
	lista_cl->ult_cl = lista_cl->prim_cl;
	lista_cl->prim_cl->prox_cl = NULL;
}
void GERAR_LISTA_OP(pont_lista_op lista_op){//GENERATE A LIST OF OPERATIONS FOR EACH CREATED CLIENT - THIRD LEVEL OF ABSTRACTION
	lista_op->prim_op = (pointerOperacao)malloc(sizeof(celulaOperacao));
	lista_op->ult_op = lista_op->prim_op;
	lista_op->prim_op->prox_op = NULL;
}
pointerAgencia BUSCAR_AGENCIA(char agencia_buscada[], pointerAgencia ppag){
	pointerAgencia aux = ppag; //GARANTEE THAT PPAG ALWAYS POINT FOR THE FIRST CELL, BY THAT, AUX WILL ALWAYS CHANGE
	while(aux != NULL && strcmp(aux->nome_ag,agencia_buscada) != 0){
		aux = aux->prox_ag;
	}
	return aux;
}
pointerCliente BUSCAR_CLIENTE(char agencia[],char cliente[],pointerAgencia ppag){
	pointerAgencia ag_buscada = BUSCAR_AGENCIA(agencia,ppag);
	pointerCliente prim_cl_ag;
	if(ag_buscada != NULL){
		prim_cl_ag = ag_buscada->ag_para_lcl->prim_cl;

		while(prim_cl_ag != NULL && strcmp(prim_cl_ag->cliente_conta.nome_cliente,cliente) != 0){
			prim_cl_ag = prim_cl_ag->prox_cl;
		}
	}
	else{
		prim_cl_ag = NULL;
	}
		//printf("cliente: %s\n",prim_cl_ag->cliente_conta.nome_cliente); 
		return prim_cl_ag;
}
pointerCliente BUSCAR_CLIENTE_ID(char agencia[],int id,pointerAgencia ppag){
	pointerAgencia ag_buscada = BUSCAR_AGENCIA(agencia,ppag);
	pointerCliente prim_cl_ag;
	if(ag_buscada != NULL){
		prim_cl_ag = ag_buscada->ag_para_lcl->prim_cl;
		while(prim_cl_ag != NULL && prim_cl_ag->cliente_conta.id_fisico != id && prim_cl_ag->cliente_conta.id_juridico != id){
			prim_cl_ag = prim_cl_ag->prox_cl;	
		}
	}
	else{
		prim_cl_ag = NULL;
	}
		return prim_cl_ag;	
}
void LER_ARQUIVO(pont_lista_ag lag, pointerAgencia pag){
	FILE *arquivo;
	char nome_txt[20];
	termos parametro;//STRUCTURE TO TAKE THE TERMS FROM INPUT
	while(1){
		printf("Write input code name (exemple: \"ex.txt\"): ");
		scanf("%s",nome_txt);
		arquivo = fopen(nome_txt,"r");
		if(arquivo == NULL) printf("ERROR: Trying to open the file\n");
		else break;		
	}
	while(!(feof(arquivo))){
		if(fgets(parametro.linha,sizeof(parametro.linha)/sizeof(char),arquivo) != NULL){
			strcpy(parametro.copia_linha,parametro.linha);
			parametro.aux = strtok(parametro.copia_linha," ");
			//strcpy(parametro.funcao,parametro.aux);
			if(strcmp(parametro.aux,"CRIAAGENCIA") == 0){
				sscanf(parametro.linha,"%s %s",parametro.funcao,parametro.agencia1);
				CRIA_AGENCIA(parametro.agencia1,lag);
			}
			else if(strcmp(parametro.aux,"INSERECLIENTE") == 0){
				sscanf(parametro.linha,"%s %s %s",parametro.funcao,parametro.cliente1,parametro.agencia1);
				INSERE_CLIENTE(parametro.agencia1,parametro.cliente1,pag);
			}
			else if(strcmp(parametro.aux,"INSERECONTA") == 0){
				sscanf(parametro.linha,"%s %s %d %s %s",parametro.funcao,parametro.tipo_conta,&parametro.id1, parametro.cliente1,parametro.agencia1);
				INSERE_CONTA(parametro.agencia1,parametro.cliente1,parametro.tipo_conta,parametro.id1,pag);
			}
			else if(strcmp(parametro.aux,"DEPOSITA") == 0){
				sscanf(parametro.linha,"%s %s %d %lf",parametro.funcao,parametro.agencia1,&parametro.id1,&(parametro.value));
				DEPOSITA(parametro.agencia1,parametro.id1,parametro.value,pag);				
			}
			else if(strcmp(parametro.aux,"SACA") == 0){
				sscanf(parametro.linha,"%s %s %d %f",parametro.funcao,parametro.agencia1,&parametro.id1,&parametro.value);
				SACA(parametro.agencia1,parametro.id1,parametro.value,pag);		
			}
			else if(strcmp(parametro.aux,"TRANSFERE") == 0){
				sscanf(parametro.linha,"%s %s %d %s %d %f",parametro.funcao,parametro.agencia1,&parametro.id1,parametro.agencia2,&parametro.id2,&parametro.value);
				TRANSFERE(parametro.agencia1,parametro.agencia2,parametro.id1,parametro.id2,parametro.value,pag);
			}
			else if(strcmp(parametro.aux,"EXTRATO") == 0){
				sscanf(parametro.linha,"%s %s %d",parametro.funcao,parametro.agencia1,&parametro.id1);
				EXTRATO(parametro.agencia1,parametro.id1,pag);				
			}
			else if(strcmp(parametro.aux,"EXCLUICONTA") == 0){
				sscanf(parametro.linha,"%s %s %d",parametro.funcao,parametro.agencia1,&parametro.id1);
				EXCLUI_CONTA(parametro.agencia1,parametro.id1,pag);				
			}
			else if(strcmp(parametro.aux,"EXCLUICLIENTE") == 0){
				sscanf(parametro.linha,"%s %s %s",parametro.funcao,parametro.agencia1,parametro.cliente1);
				EXCLUI_CLIENTE(parametro.agencia1,parametro.cliente1,pag);	
			}
			else if(strcmp(parametro.aux,"EXCLUIAGENCIA") == 0){
				sscanf(parametro.linha,"%s %s",parametro.funcao,parametro.agencia1);
				EXCLUI_AGENCIA(parametro.agencia1,pag);				
			}
			else if(strcmp(parametro.aux,"IMPRIMETUDO\n") == 0||strcmp(parametro.aux,"IMPRIMETUDO") == 0){
				IMPRIME_TUDO(pag);
			}
			else{
				printf("Chamada inexistente!\n");
			}
		}
	}
}
//FUNCTIONS - AGENCY MANAGEMENT
void CRIA_AGENCIA(char name_agencia[],pont_lista_ag lista_ag){
	lista_ag->ult_ag->prox_ag = (pointerAgencia)malloc(sizeof(celulaAgencia));
	lista_ag->ult_ag = lista_ag->ult_ag->prox_ag;
	strcpy(lista_ag->ult_ag->nome_ag,name_agencia);
	lista_ag->ult_ag->prox_ag = NULL;
	lista_ag->ult_ag->ag_para_lcl = (pont_lista_cl)malloc(sizeof(listaCliente));//Jesus cHRIST
	GERAR_LISTA_CL(lista_ag->ult_ag->ag_para_lcl);
}
void EXCLUI_AGENCIA(char name_agencia[], pointerAgencia ppag){
	pointerAgencia aux1,aux2;
	aux1 = ppag;
	aux2 = ppag->prox_ag;
	while(aux2 != NULL && strcmp(aux2->nome_ag,name_agencia)!= 0){
		aux1 = aux2;
		aux2 = aux2->prox_ag;
	}
	if(aux2 == NULL){
		printf("Error: Op - EXCLUIAGENCIA::Agencia - %s - DO NOT EXIST IN THIS DATASET!\n",name_agencia);
	}
	else if(aux2 != NULL){
		aux1->prox_ag = aux2->prox_ag;
		free(aux2);
		printf("Agencia excluida!\n");
	}
	return;
}
//FUNCTIONS - CLIENT MANAGEMENT
void INSERE_CLIENTE(char agencia[], char novo_cliente[],pointerAgencia ppag){
	pointerAgencia ag_buscada = BUSCAR_AGENCIA(agencia,ppag);
	if(ag_buscada != NULL){
		ag_buscada->ag_para_lcl->ult_cl->prox_cl = (pointerCliente)malloc(sizeof(celulaCliente));
		ag_buscada->ag_para_lcl->ult_cl = ag_buscada->ag_para_lcl->ult_cl->prox_cl;
		strcpy(ag_buscada->ag_para_lcl->ult_cl->cliente_conta.nome_cliente,novo_cliente);
		ag_buscada->ag_para_lcl->ult_cl->cliente_conta.id_fisico = 0;
		ag_buscada->ag_para_lcl->ult_cl->cliente_conta.id_juridico = 0;
		ag_buscada->ag_para_lcl->ult_cl->cliente_conta.tipo_fisico = 0;
		ag_buscada->ag_para_lcl->ult_cl->cliente_conta.tipo_juridico = 0;
		ag_buscada->ag_para_lcl->ult_cl->prox_cl = NULL;
		ag_buscada->ag_para_lcl->ult_cl->cl_para_op = (pont_lista_op)malloc(sizeof(listaOperacao));
		GERAR_LISTA_OP(ag_buscada->ag_para_lcl->ult_cl->cl_para_op);
	}
	else{
		printf("ERROR: OP - INSERECLIENTE::Agencia - %s - DID NOT WORK!\n",agencia);
	}

}
void EXCLUI_CLIENTE(char agencia[],char cliente[],pointerAgencia ppag){
	pointerAgencia ag_buscada = BUSCAR_AGENCIA(agencia,ppag);
	if(ag_buscada != NULL){
		pointerCliente aux1, aux2;
		aux1 = ag_buscada->ag_para_lcl->prim_cl;
		aux2 = aux1->prox_cl;
		while(aux2 != NULL && strcmp(aux2->cliente_conta.nome_cliente,cliente) != 0){	
			aux1 = aux2;
			aux2 = aux2->prox_cl;
		}
		if(aux2 != NULL){
			aux1->prox_cl = aux2->prox_cl;
			free(aux2);
			printf("CLIENT REMOVED!\n");
		}
		else{
			printf("ERROR: OP - EXCLUICLIENTE:: Cliente - %s - NOT FOUND - %s.\n",cliente,agencia);
		}	
	}
	else{
		printf("ERROR: OP - EXCLUICLIENTE:: Agencia - %s - NOT FOUND THIS CLIENT!\n",agencia);
	}
}
//FUNCTIONS - ACCOUNT MANAGEMENT
void INSERE_CONTA(char agencia[], char cliente[],char tipo[],int id, pointerAgencia ppag){
	pointerCliente p_cliente_buscado = BUSCAR_CLIENTE(agencia,cliente,ppag);
	if(p_cliente_buscado != NULL){
		if(strcmp(tipo,"PESSOAFISICA") == 0){
			p_cliente_buscado->cliente_conta.id_fisico = id;
			p_cliente_buscado->cliente_conta.tipo_fisico = 1;		
		}
		else if(strcmp(tipo,"PESSOAJURIDICA") == 0){
			p_cliente_buscado->cliente_conta.id_juridico = id;
			p_cliente_buscado->cliente_conta.tipo_juridico = 1;
		}
		else{
			printf("ERROR: OP - INSERECONTA:: DONT EXIST THIS TYPE OF ACCOUNT!\n");
		}
	}
	else{
		printf("ERROR: OP - INSERECONTA:: DO NOT EXIST CLIENT OR ANY AGENCY\n",cliente,agencia);
	}
}
void EXCLUI_CONTA(char agencia[],int id, pointerAgencia ppag){
	pointerCliente p_cliente_buscado = BUSCAR_CLIENTE_ID(agencia,id,ppag);
	if(p_cliente_buscado != NULL){
		if(id == p_cliente_buscado->cliente_conta.id_fisico){
			p_cliente_buscado->cliente_conta.id_fisico = 0;
			p_cliente_buscado->cliente_conta.tipo_fisico = 0;
			printf("FISIC ACCOUNT ERASED!\n");		
		}
		else if(id == p_cliente_buscado->cliente_conta.id_juridico){
			p_cliente_buscado->cliente_conta.id_juridico = 0;
			p_cliente_buscado->cliente_conta.tipo_juridico = 0;
			printf("JURIDIC ACCOUNT ERASED!\n");
		}
		else{
			printf("ERROR: OPERATION - EXCLUICONTA:: DO NOT EXIST THIS ACCOUNT FOR THIS CLIENT!\n ID WRONG!\n");
		}
	}
	else{
		printf("ERROR: OPERATION - EXCLUICONTA:: DO NOT EXIST CLIENT OR AGENCY\n",p_cliente_buscado->cliente_conta.nome_cliente,agencia);
	}
}
//FUNCTIONS - OPERATIONS
void SACA(char agencia[], int idConta, double valor,pointerAgencia ppag){
	pointerCliente pcID = BUSCAR_CLIENTE_ID(agencia,idConta,ppag);
	if(pcID != NULL){
		pcID->cl_para_op->ult_op->prox_op = (pointerOperacao)malloc(sizeof(celulaOperacao));
		pcID->cl_para_op->ult_op = pcID->cl_para_op->ult_op->prox_op;
		pcID->cl_para_op->ult_op->caracteristicas.valor = valor;
		strcpy(pcID->cl_para_op->ult_op->caracteristicas.tipo_op,"SACA");
		pcID->cl_para_op->ult_op->prox_op = NULL;
	}
	else{
		printf("ERROR: OPERATION - SACA:: ID OR AGENCY NOT FOUND\n");
	}
}
void DEPOSITA(char agencia[], int idConta, double valor,pointerAgencia ppag){
	pointerCliente pcID = BUSCAR_CLIENTE_ID(agencia,idConta,ppag);
	if(pcID != NULL){
		pcID->cl_para_op->ult_op->prox_op = (pointerOperacao)malloc(sizeof(celulaOperacao));
		pcID->cl_para_op->ult_op = pcID->cl_para_op->ult_op->prox_op;
		pcID->cl_para_op->ult_op->caracteristicas.valor = valor;
		strcpy(pcID->cl_para_op->ult_op->caracteristicas.tipo_op,"DEPOSITA");
		pcID->cl_para_op->ult_op->prox_op = NULL;
	}
	else{
		printf("ERROR: OPERATION - DEPOSITA:: ID OR AGENCY NOT FOUND\n");
	}
}
void TRANSFERE(char agenciaOrigem[],char agenciaDest[],int idOrigem, int idDest,double valor, pointerAgencia ppag){
	pointerCliente pcO = BUSCAR_CLIENTE_ID(agenciaOrigem,idOrigem,ppag);
	pointerCliente pcD = BUSCAR_CLIENTE_ID(agenciaDest,idDest,ppag);
	if(pcO != NULL && pcD != NULL){
		pcO->cl_para_op->ult_op->prox_op = (pointerOperacao)malloc(sizeof(celulaOperacao));
		pcO->cl_para_op->ult_op = pcO->cl_para_op->ult_op->prox_op;	
		//ORIGIN DATA
		strcpy(pcO->cl_para_op->ult_op->caracteristicas.tipo_op,"TRANSFERE");
		pcO->cl_para_op->ult_op->caracteristicas.valor = valor;
		pcO->cl_para_op->ult_op->caracteristicas.id_trans = idDest;	
		//END
		pcD->cl_para_op->ult_op->prox_op = (pointerOperacao)malloc(sizeof(celulaOperacao));
		pcD->cl_para_op->ult_op = pcD->cl_para_op->ult_op->prox_op;
		//GOAL DATA
		strcpy(pcD->cl_para_op->ult_op->caracteristicas.tipo_op,"TRANSFERE");
		pcD->cl_para_op->ult_op->caracteristicas.valor = valor;
		pcD->cl_para_op->ult_op->caracteristicas.id_trans = idOrigem;
		printf("SUCESS IN YOUR TRANSFER!\n");		
	}
	else{
		printf("ERROR: OPERATION - TRANSFERE:: ID OR AGENCY NOT FOUND (ORIGIN OR DESTINY)\n");
	}
	
}
void EXTRATO(char agencia[], int idConta,pointerAgencia ppag){
	pointerCliente pcID = BUSCAR_CLIENTE_ID(agencia,idConta,ppag);
	if(pcID != NULL){
		pointerOperacao aux = pcID->cl_para_op->prim_op->prox_op;
		printf("EXTRACT %s %d\n",agencia,idConta);
		while(aux != NULL){		
			if(strcmp(aux->caracteristicas.tipo_op,"TRANSFERE") == 0 || strcmp(aux->caracteristicas.tipo_op,"RECEBE") == 0){
				printf("	%s %.2lf TO %d\n",aux->caracteristicas.tipo_op,aux->caracteristicas.valor,aux->caracteristicas.id_trans);
			}
			else{
				printf("	%s %.2lf\n",aux->caracteristicas.tipo_op,aux->caracteristicas.valor);
			}
			aux = aux->prox_op;	
		}
	}
	else{
		printf("ERROR: OPERATION - EXTRATO:: ID OR AGENCY NOT FOUND\n");
	}
}
//FUNCTION - PRINT ALL
void IMPRIME_TUDO(pointerAgencia ppag){
	pointerAgencia aux = ppag->prox_ag;
	while(aux != NULL){
		printf("AGENCIA %s\n",aux->nome_ag);
		pointerCliente pc = aux->ag_para_lcl->prim_cl->prox_cl;
		while(pc != NULL){
			printf("	CLIENTE %s\n",pc->cliente_conta.nome_cliente);
			if(pc->cliente_conta.tipo_fisico == 1) printf("		CONTA PESSOAFISICA %d\n",pc->cliente_conta.id_fisico);
			if(pc->cliente_conta.tipo_juridico == 1) printf("		CONTA PESSOAJURIDICA %d\n",pc->cliente_conta.id_juridico);
			pc = pc->prox_cl;
		}	
		aux= aux->prox_ag;
	}	
}
