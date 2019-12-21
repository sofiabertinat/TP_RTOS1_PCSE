/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[SensorIR.h]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 2.0.0
 * Creation Date: 2019/12/17
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef _SENSORIR_H_
#define _SENSORIR_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"

/*=====[Definition macros of public constants]===============================*/

#define S0		     GPIO0
#define S1		     GPIO1
#define S2		     GPIO2
#define S3		     GPIO3
#define SENSOR_SIG   CH1

static gpioMap_t s[4]={S0,S1,S2,S3};

/*=====[Prototypes (declarations) of public functions]=======================*/

uint16_t LecturaSensorIR(int sensor);

#endif /* _SENSORIR_H_ */
