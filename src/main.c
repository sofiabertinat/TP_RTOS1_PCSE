/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[main.c]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 2.0.0
 * Creation Date Version 1.0.0: 2019/10/09
 * Creation Date Version 2.0.0: 2019/12/04
 */

#include "main.h"

TaskHandle_t xHandleTecla_task = NULL;
TaskHandle_t xHandleconfig_task = NULL;

int main( void )
{
	   // Inicializar y configurar la plataforma
	   boardConfig();

	   // UART for debug messages
	   debugPrintConfigUart( UART_USB, 115200 );
	   printf( "Medida de la altura del pasto con freeRTOS y sAPI.\r\n" );
	   
	   // Inicializar LCD
	   i2cInit( I2C0, 100000 );
	   // Inicializar LCD de 16x2 (caracteres x lineas) con cada caracter de 5x2 pixeles
       lcdInit( 16, 2, 5, 8 );
       lcdGoToXY( 0, 0 ); // Poner cursor en 0, 0
	   lcdSendStringRaw( "Bienvenidos" );

	   adcInit( ADC_ENABLE);

	   // Inicializar la IMU
	   //mpu9250Init(MPU9250_ADDRESS_0 );

      xBinarySemaphore = xSemaphoreCreateBinary();
      xMutexSemaphore = xSemaphoreCreateMutex();

	  /*Adquiere datos de arreglo de sensores IR*/
	  xTaskCreate( handlerIR, (const char *)"HandlerlecturaSensoresIR", configMINIMAL_STACK_SIZE*10, &promedioAlturaPasto, tskIDLE_PRIORITY+2, NULL);

	  // Crear tareas de Teclas en freeRTOS
	  xTaskCreate( Tecla_task, (const char *)"Tec1", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, &xHandleTecla_task);

	  /* Tarea permite configurar equipo desde la UART*/
	  xTaskCreate( config_task, (const char *)"equipoConfig", configMINIMAL_STACK_SIZE*2, 0,  tskIDLE_PRIORITY+5,  &xHandleconfig_task );

	 /*Tarea muestra valor promedio de las medidas en pantalla LCD*/
	  xTaskCreate(tareaLCD, (const char *)"lcd", configMINIMAL_STACK_SIZE*2,  &promedioAlturaPasto, tskIDLE_PRIORITY+4, 0 );

	   // Iniciar scheduler
	   vTaskStartScheduler();

	   while( TRUE ) {
	      // Si cae en este while 1 significa que no pudo iniciar el scheduler
	   }

	   return 0;
}

/*-----------------------------------------------------------*/

/* Funcion que realiza la tarea LCD. Muestra valor promedio de las medidas en pantalla LCD*/
void tareaLCD(void* taskParmPtr){

   char promedio;
   int AlturaPasto;

   lcdGoToXY( 0, 0 ); // Poner cursor en 0, 0
   lcdSendStringRaw( "Altura promedio" );

   // Tarea periodica cada 100 ms
   portTickType xPeriodicityLCD =  10000 / portTICK_RATE_MS;
   portTickType xLastWakeTimeLCD = xTaskGetTickCount();

	for( ;; ) {

		  xSemaphoreTake(xMutexSemaphore, portMAX_DELAY );
		  AlturaPasto = (*(int*) taskParmPtr);

		  itoa(AlturaPasto, &promedio);
	      lcdGoToXY( 0, 1 );
	      lcdSendStringRaw( &promedio );
	      lcdSendStringRaw( " cm" );

	      xSemaphoreGive(xMutexSemaphore);

	      //lcdCursorSet( LCD_CURSOR_OFF ); // Apaga el cursor
	      //lcdClear(); // Borrar la pantalla
	      //lcdGoToXY( 0, 0 );

	  	  // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
	  	  vTaskDelayUntil( &xLastWakeTimeLCD, xPeriodicityLCD );
	}
}

/*-----------------------------------------------------------*/

/* Funcion que realiza la tarea de configuracion. Permite configurar equipo desde la UART*/
void config_task(void* taskParmPtr ){

	uint8_t metros = 0;
	bool recibido=0;

	printf( "Se espera a que el usuario escriba la cantidad de metros que quiere sensar,\r\n" );

	while(recibido==0){
		recibido = uartReadByte( UART_USB, &metros );
	}

	printf( "Se recibio la cantidad de metros que quiere sensar,\r\n" );

    CalculoDuracionSensado(metros, &duracionSensado);

    xSemaphoreGive(xMutexSemaphore);

    if( xHandleconfig_task != NULL )
    {
    	vTaskDelete( xHandleconfig_task );
    }

}

/*-----------------------------------------------------------*/

/* Funcion que realiza la tarea de sensores IR. Adquiere datos de arreglo de sensores IR*/
void handlerIR(void* taskParmPtr){

   int* promedioAltura;

   // Tarea periodica cada 5 ms
   portTickType xPeriodicityIR =  500 / portTICK_RATE_MS;
   portTickType xLastWakeTimeIR = xTaskGetTickCount();

   bool_t semaforo=0;

   promedioAltura = (int*) taskParmPtr;

   for( ;; ) {

	  //printf(" handlerIR is ranning \r\n");
	  if(semaforo==0){
		  xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );
		  semaforo=1;
	  }

	  xSemaphoreTake( xMutexSemaphore, portMAX_DELAY );
      CalculoAlturaPasto(promedioAltura, &contador);
      xSemaphoreGive(xMutexSemaphore);

  	  //Me fijo si ya recorri toda la distancia que se quería sensar
  	  if(contador==duracionSensado){

  		  contador=0;
  		  semaforo = 0;
  		  LedApagar(LUZ_VERDE);

  		  /* Tarea permite configurar equipo desde la UART*/
  		  xTaskCreate( config_task, (const char *)"equipoConfig", configMINIMAL_STACK_SIZE*2, 0,  tskIDLE_PRIORITY+5,   &xHandleconfig_task );
  		 // Crear tareas de Teclas en freeRTOS
  		  xTaskCreate( Tecla_task, (const char *)"Tec1", configMINIMAL_STACK_SIZE*2, 0, tskIDLE_PRIORITY+1, &xHandleTecla_task);
   	  }else{
   		  contador++;
  	  }

  	  // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
  	  vTaskDelayUntil( &xLastWakeTimeIR, xPeriodicityIR );

    }

}

/*-----------------------------------------------------------*/

// Implementacion de funcion de la tarea genérica Tecla
void Tecla_task( void* taskParmPtr )
{
	bool_t botonPresionado=0;

	//for( ;; ) {

		TECInicializarMEF();
		printf("Se espera el accionar del boton de inicio\r\n");
		while(botonPresionado==0){
			TEC_antirebote_MEF(TEC1,&botonPresionado);
		}
		if(botonPresionado==1){
			printf("Comienzo de sensado\r\n");
			xSemaphoreGive(xBinarySemaphore);
		}
	//}

	if( xHandleTecla_task != NULL )
	{
		vTaskDelete( xHandleTecla_task );
	}
}

/*==================[end of file]============================================*/

