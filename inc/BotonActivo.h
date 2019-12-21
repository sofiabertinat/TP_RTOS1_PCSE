/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[BotonActivo.h]===========================================================
 * Copyright YYYY Author Compelte Name <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 2.0.0
 * Creation Date Version 1.0.0: 2019/10/09
 * Creation Date Version 2.0.0: 2019/12/19
 */

#ifndef _BOTONACTIVO_H_
#define _BOTONACTIVO_H_

/*=====[Inclusions of public function dependencies]==========================*/

#include "sapi.h"
#include "leds.h"


/*=====[Definitions of public data types]====================================*/

typedef enum{
   BOTON_UP,
   BOTON_DOWN,
   BOTON_FALLING,
   BOTON_RISING
} EstadoBoton_t;

/*=====[Prototypes (declarations) of public functions]=======================*/

void BotonError( void );
void TECInicializarMEF(void);
void TEC_antirebote_MEF( gpioMap_t tecla, bool_t *botonPresionado);
void BotonPresionado(bool_t *botonPresionado);
void BotonLiberado( void );

#endif /* _BOTONACTIVO_H_ */
