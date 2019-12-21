/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[AlturaPasto.h]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 2.0.0
 * Creation Date Version 1.0.0: 2019/10/09
 * Creation Date Version 2.0.0: 2019/12/04
 */


#ifndef _ALTURAPASTO_H_
#define _ALTURAPASTO_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"
#include "appMpu9250.h"
#include "../../../TrabajoFinal/TP_RTOS1_PCSE/inc/leds.h"
#include "../../../TrabajoFinal/TP_RTOS1_PCSE/inc/SensorIR.h"


/*=====[Definition macros of public constants]===============================*/

#define TIEMPO_LECTURA     5 // ms
#define CANT_SENSORES      16


/*=====[Definitions of public data types]====================================*/


static bool estadoSensor[CANT_SENSORES]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/*=====[Prototypes (declarations) of public functions]=======================*/

void CalculoDuracionSensado(int metros, int *duracionSensado);
void CalculoAlturaPasto(int *promedioAlturaPasto, int *contador);
void descartarMedida(bool_t *desnivel);


#endif /* _ALTURAPASTO_H_ */

