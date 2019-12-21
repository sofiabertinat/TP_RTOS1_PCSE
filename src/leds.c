/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[leds.c]===========================================================
 * Copyright YYYY Author Compelte Name <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 1.0.0
 * Creation Date: 2019/10/09
 */
 
#include "leds.h"


void LedEncender(gpioMap_t lampara){

	gpioWrite( lampara, ON );

}

void LedApagar(gpioMap_t lampara){

	gpioWrite( lampara, OFF );

}

