/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[main.h]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 2.0.0
 * Creation Date Version 1.0.0: 2019/10/09
 * Creation Date Version 2.0.0: 2019/12/04
 */

/*==================[inlcusiones]============================================*/

// Includes de FreeRTOS
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"   //Motor del OS
#include "task.h"		//Api de control de tareas y temporización
#include "semphr.h"		//Api de sincronización (sem y mutex)
#include "queue.h"      //Api de colas

// sAPI header
#include "sapi.h"
#include "board.h"
#include "AlturaPasto.h"
#include "leds.h"
#include "BotonActivo.h"
#include "appMpu9250.h"
#include "funAux.h"

static int promedioAlturaPasto = 0;
static int contador = 1;
static int duracionSensado = 0;

static SemaphoreHandle_t xBinarySemaphore;
static SemaphoreHandle_t xMutexSemaphore;

void config_task(void* taskParmPtr );
void handlerIR(void* taskParmPtr);
void tareaLCD(void* taskParmPtr );
void Tecla_task( void* taskParmPtr );

DEBUG_PRINT_ENABLE

