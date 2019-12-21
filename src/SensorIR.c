
/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[SensorIR.c]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 2.0.0
 * Creation Date: 2019/12/17
 */

#include "../../../TrabajoFinal/TP_RTOS1_PCSE/inc/SensorIR.h"


uint16_t LecturaSensorIR(int sensor){

	int j=0;
    int i=0;
	bool_t valor=0;
	int aux, resto;

	aux = sensor - 1;

	for(j=1; j<5; j++){

		resto = aux % 2;
		aux = aux / 2;
		if(resto!=0){
			valor = 1;
		}else{
			valor = 0;
		}
        i=j-1;
        gpioWrite( s[i], valor );
	}
	return(adcRead( SENSOR_SIG));

}

