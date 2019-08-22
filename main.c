#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "bankList.h"

/* CODE RESTRICTIONS
- It's necessary to use real values using "." NOT ","
- It's necessary to use simple names, for example the code doesn't support "name last name" or "agency WTF"
- The program can not say the difference between "01" and "1"
- This code is a not Circular List, that means that the first point reference is the pointer for the first agency
*/

int main(){
	//Init
	pont_lista_ag ponteiroLA = (pont_lista_ag) malloc(sizeof(listaAgencia));
	GERAR_LISTA_AG(ponteiroLA);
	pointerAgencia ppag = ponteiroLA->prim_ag;//Ponteiro para primeira agencia refer�ncia
	// Read input.txt
	LER_ARQUIVO(ponteiroLA,ppag);
	// Hold On!
   system("pause");  
   return 0;
}
