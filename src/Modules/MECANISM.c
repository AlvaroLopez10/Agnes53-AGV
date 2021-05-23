/*
k * MECANISM.c
 *
 *  Created on: 07/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "MECANISM.h"
#include "../Init_Settings/INIT_FTM.h"
#include "../Init_Settings/INIT_UART2.h"
#include "../Functions/MANUAL.h"

//W Baja
//M Sube

unsigned char direction = 'W'; //W Baja //M Sube
unsigned int enable=0; //0 Apagado //1 Movimiento
unsigned int limit=0; //0 Abajo //1 Arriba
unsigned int arrived = 1; //0 No a llegado //Acaba de llegar
extern unsigned char command_manual;

void mecanismUp(void){

	PTA->PCOR |= (1<<11);
	PTA->PSOR |= (1<<17);
	PWM(0, 0, 10);
}

void mecanismDown(void){
	PTA->PCOR |= (1<<17);
    PTA->PSOR |= (1<<11);
    PWM(0, 0, 10);
}

void mecanismStop(void){
	PTA->PSOR |= (1<<11) + (1<<17);
}

void mecanism (void){
	direction = command_manual;

	if ((PTD -> PDIR & (1<<9)) == (1<<9)){
		limit = 0;
	}
	if ((PTD -> PDIR & (1<<2)) == (1<<2)){
		limit = 1;
	}

	if (enable == 0) {						//E = 0
		if (limit == 0) {
			if (direction == 'M') {
				enable = 1;
				mecanismUp();
				arrived = 0;
			}else{
				enable = 0;
				mecanismStop();
				arrived = 1;
			}//else D
		}else {
			if(direction == 'W'){
				enable = 1;
				mecanismDown();
				arrived = 0;
			}else {
				enable = 0;
				mecanismStop();
				arrived = 1;
			}//else D
		}//else L
	}else {									//E = 1
		if (direction == 'M') {
			if (limit == 0) {
				enable = 1;
				mecanismUp();
				arrived = 0;
			}else{
				enable = 0;
				mecanismStop();
				arrived = 1;
			}//else L
		}else {
			if(limit == 1){
				enable = 1;
				mecanismDown();
				arrived = 0;
			}else {
				enable = 0;
				mecanismStop();
				arrived = 1;
			}//else L
		}//else D
	}//else E = 1

}

