/*=====[TP_RTOS1_PCSE]===========================================================
/*=====[AlturaPasto.c]===========================================================
 * Copyright 2019 Sofía Bertinat <sofiabertonatv@gmail.com>
 * All rights reserved.
 * License:
 *
 * Version: 2.0.0
 * Creation Date Version 1.0.0: 2019/10/09
 * Creation Date Version 2.0.0: 2019/12/04
 */
 
#include "../../../TrabajoFinal/TP_RTOS1_PCSE/inc/AlturaPasto.h"

/*=====[Definitions of private global variables]=============================*/

static int suma = 0;



/*=====[Implementations of public functions]=================================*/

 // Función calculo duracón del sensado
 void CalculoDuracionSensado(int metros, int *duracionSensado){

	float duracion=0;

	duracion = metros/0.0275; // si v = 5,5 m/s --> en 5ms recorre 0,0275m
	(*duracionSensado) = (int)duracion;

 }

 //  Función Actualizar MEF
 void CalculoAlturaPasto(int *promedioAlturaPasto, int *contador){

	 int j=0;
	 int altura=0;
	 int i=0;
	 int cont=1;
	 bool_t desnivel;
	 uint16_t lecturaAnalog;

	if((*contador)==0){
		suma=0;
	}

	//Leo el estado de los sensores IR
	for (j=1; j<=CANT_SENSORES; j++){
		lecturaAnalog=LecturaSensorIR(j);
		//printf("valor analogico %i \n\r",lecturaAnalog);
		if(lecturaAnalog>=1010){
			estadoSensor[j]=1;
		}else{
			estadoSensor[j]=0;
		}
		//printf("valor %d \n\r",estadoSensor[j]);
	}	
			  
	altura=0;
	i=CANT_SENSORES;
	//determino la altura del pasto, dependiendo del sensor mas alto activo
	//se establece que el sensor 1 esta a 50mm del suelo, y el resto distan 20mm entre sí
	while(i>0 && altura == 0){
		if(estadoSensor[i]==1){
			altura = 50 + (i-1)*20;
			//printf("altura %i \n\r",altura);
		}
		i--;
	}

	//desnivel=0;
	//descartarMedida(&desnivel);
	//if(desnivel==0){
		//guardo la suma de todas las aturas del pasto para poder calcular el promedio
		suma = suma + altura;
		cont = (*contador);
		//calculo el promedio de la altura del pasto hasta el momento
		(*promedioAlturaPasto) = suma/cont;
		printf("La altura promedio del pasto en mm es: %i \n\r",(*promedioAlturaPasto));
	//}else {
		//printf("Se descarto la medida \n\r");
	//}

}

 void descartarMedida(bool_t *desnivel){

	 float rad_x, rad_y, rad_z;
	 float tolmax, tolmin;

	 MedidaGiroscopio(&rad_x, &rad_y, &rad_z);
	 tolmax = 3.14/180;
	 tolmin = - 3.14/180;

	 if(rad_x>tolmax|rad_x<tolmin |rad_y>tolmax|rad_y<tolmin |rad_z>tolmax|rad_x<tolmin ){
		 (*desnivel)=1;
	 }

 }


