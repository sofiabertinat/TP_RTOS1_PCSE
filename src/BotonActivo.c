/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[BotonActivo.c]===========================================================
 * Copyright YYYY Author Compelte Name <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 2.0.0
 * Creation Date Version 1.0.0: 2019/10/09
 * Creation Date Version 2.0.0: 2019/12/19
 */
 

#include "BotonActivo.h"

static EstadoBoton_t EstadoTec;

void BotonPresionado( bool_t *botonPresionado)
{
	(*botonPresionado)=1;
	LedEncender(LUZ_VERDE);

}

void BotonLiberado( void )
{
	printf("Boton inicio liberado\r\n");

}

void BotonError( void )
{
   EstadoTec = BOTON_UP;
}

void TECInicializarMEF( void )
{
   EstadoTec = BOTON_UP; 
}


void TEC_antirebote_MEF( gpioMap_t tecla, bool_t *botonPresionado)
{
   static bool_t flagFalling = FALSE;
   static bool_t flagRising = FALSE;

   static int contFalling = 0;
   static int contRising = 0;

   switch( EstadoTec ){

      case BOTON_UP:
         
         if( !gpioRead(tecla) ){
            EstadoTec = BOTON_FALLING;
         }
      break;

      case BOTON_DOWN:
         
         if( gpioRead(tecla) ){
            EstadoTec = BOTON_RISING;
         }
      break;

      case BOTON_FALLING:
        
         if( flagFalling == FALSE ){
            flagFalling = TRUE;
          }
       
         if( contFalling >= 10 ){
            if( !gpioRead(tecla) ){
               EstadoTec = BOTON_DOWN;
               BotonPresionado(botonPresionado);
            } else{
               EstadoTec = BOTON_UP;
            }
            contFalling = 0;
         }

         contFalling++;
 
         if( EstadoTec != BOTON_FALLING ){
            flagFalling = FALSE;
         }
      break;

      case BOTON_RISING:
         
         if( flagRising == FALSE ){
            flagRising = TRUE;
         }
  
         if( contRising >= 10 ){
            if( gpioRead(tecla) ){
            	EstadoTec = BOTON_UP;
                BotonLiberado();
            } else{
            	EstadoTec = BOTON_DOWN;
            }

            contRising = 0;
         }
         contRising++;

         if( EstadoTec != BOTON_RISING ){
            flagRising = FALSE;
         }
      break;

      default:
         BotonError();
      break;
   }
}

