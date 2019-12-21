/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[funAux.c]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date Version 1.0.0: 2019/12/04
 */
 
#include "funAux.h"

/*=====[Definitions of private global variables]=============================*/


/*=====[Implementations of public functions]=================================*/

void itoa(int valor, char* str) {

	static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* wstr = str;
    int cociente, resto;

    *wstr='\0';
    if(valor>99 && valor<1000){
    	cociente = valor/100;
    	resto = valor % 100;
    	*wstr++= num[cociente];
    	cociente = resto/10;
    	resto = cociente %10 ;
    	*wstr++= num[cociente];
    	*wstr++= num[resto];
    }else if(valor>9 && valor<100){
    	cociente = valor/10;
    	resto = valor %10 ;
    	*wstr= num[cociente];
    	*wstr++= num[resto];
    }else if (valor<10){
    	*wstr= num[valor];
    }else{
    	*wstr=num[0];
    }

    *wstr++='\0';

    // Reverse string
    //strreverse(str,wstr-1);


}

void strreverse(char* begin, char* end) {
    char aux;

    while(end>begin)
        aux=*end, *end--=*begin, *begin++=aux;
}


