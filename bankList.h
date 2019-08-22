// Threatened Lists - Bank Simulation Code
#ifndef BANKLIST_H_   /* Include guard */
#define BANKLIST_H_

typedef struct dados{ //Structure: Client Account Data
	char nome_cliente[20];//Client name
	int tipo_fisico;//INT Value to say if the person is normal - 1 - or juridic (company) - 0 -
	int tipo_juridico;//INT Value to say if the person is normal - 0 - or juridic (company) - 1 -
	int id_fisico;//ID for tipo_fisico
	int id_juridico;//ID for tipo_juridico
}dados;

typedef struct oper_dados{//Structure: Operations
	char tipo_op[20];
	double valor;
	int id_trans;
}oper_dados;

typedef struct termos{//Structure: Auxiliar for take the inputs from txt file
	char *aux;//Takes the first term to help comparison in function LER_ARQUIVO
	char funcao[15];
	char linha[100];
	char copia_linha[100];
	char agencia1[15];
	char agencia2[15];
	char cliente1[15];
	char cliente2[15];
	char tipo_conta[15];
	int id1;
	int id2;
	double value;
}termos;

//STRUCTURE: POINTERS TO LIST STRUCTURE
typedef struct listaAgencia* pont_lista_ag;
typedef struct listaCliente* pont_lista_cl;
typedef struct listaOperacao* pont_lista_op;

//STRUCTURE: POINTERS TO STRUCT CELL FROM EVERY LIST
typedef struct celulaAgencia *pointerAgencia;
typedef struct celulaCliente *pointerCliente;
typedef struct celulaOperacao *pointerOperacao;

//STRUCTURE: AGENCY
typedef struct celulaAgencia{
	char nome_ag[20];
	pointerAgencia prox_ag;
	pont_lista_cl ag_para_lcl;
}celulaAgencia;
typedef struct listaAgencia{
	pointerAgencia prim_ag,ult_ag;
}listaAgencia;

//Define Relation - STRUCTURE: CLIENT - ACCOUNT
typedef struct celulaCliente{
	dados cliente_conta;
	pointerCliente prox_cl;
	pont_lista_op cl_para_op;
}celulaCliente;
typedef struct listaCliente{
	pointerCliente prim_cl,ult_cl;
}listaCliente;

//Define Relation - STRUCTURE: OPERATIONS
typedef struct celulaOperacao{
	oper_dados caracteristicas;
	pointerOperacao prox_op;
}celulaOperacao;
typedef struct listaOperacao{
	pointerOperacao prim_op,ult_op;
}listaOperacao;

//DEFINING FUNCTIONS - GENERAL USE
void GERAR_LISTA_AG(pont_lista_ag lista_ag);//GENERATE LISTS FOR AGENCY
void GERAR_LISTA_CL(pont_lista_cl lista_cl);//GENERATE DYNAMICS LISTS FOR CLIENT - ACCOUNT
void GERAR_LISTA_OP(pont_lista_op lista_op);//GENERATE DYNAMICS LISTS FOR OPERATIONS
void LER_ARQUIVO(pont_lista_ag lag, pointerAgencia pag);//READ INPUT FILE
pointerAgencia BUSCAR_AGENCIA(char agencia_buscada[], pointerAgencia ppag);//RETURNS A POINTER THAT POINTS FOR A CELL TYPE AGENCY SEARCHED BY NAME
pointerCliente BUSCAR_CLIENTE(char agencia[],char cliente[],pointerAgencia ppag);//RETURNS A POINTER THAT POINTS FOR A CELL TYPE CLIENT SEARCHED BY NAME
pointerCliente BUSCAR_CLIENTE_ID(char agencia[],int id,pointerAgencia ppag);//RETURNS A POINTER THAT POINTS FOR A CELL TYPE CLIENT SEARCHED BY ID
//DEFINING FUNCTIONS - AGENCY MANAGEMENT
void CRIA_AGENCIA(char name_agencia[],pont_lista_ag lista_ag); //GENERATE A AGENCY
void EXCLUI_AGENCIA(char name_agencia[], pointerAgencia ppag); // ERASE A AGENCY
//DEFINING FUNCTIONS - CLIENT MANAGEMENT
void INSERE_CLIENTE(char agencia[], char novo_cliente[],pointerAgencia ppag); //INSERT A NEW CLIENT
void EXCLUI_CLIENTE(char agencia[],char cliente[],pointerAgencia ppag); // ERASE A CLIENT
//DEFINING FUNCTIONS - ACCOUNT MANAGEMENT
void INSERE_CONTA(char agencia[], char cliente[],char tipo[],int id, pointerAgencia ppag); // INSERT A NEW ACCOUNT FOR A CLIENT
void EXCLUI_CONTA(char agencia[],int id, pointerAgencia ppag); // ERASE A ACCOUNT FROM A CLIENT
//DEFINING FUNCTIONS - OPERATIONS
void SACA(char agencia[], int idConta,double valor,pointerAgencia ppag); // WITHDRAWAL MONEY
void DEPOSITA(char agencia[], int idConta,double valor,pointerAgencia ppag); // DEPOSIT MONEY
void TRANSFERE(char agenciaOrigem[],char agenciaDest[],int idOrigem, int idDest,double valor, pointerAgencia ppag); // TRANSFER MONEY BETWEEN CLIENTS
void EXTRATO(char agencia[], int idConta,pointerAgencia ppag); // EXTRACT FROM YOUR ACCOUNT
void IMPRIME_TUDO(pointerAgencia ppag); // PRINT ALL

#endif