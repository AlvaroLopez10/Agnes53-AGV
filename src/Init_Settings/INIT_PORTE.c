/*
 * INIT_PORTE.c
 *
 *  Created on: 13/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT_PORTE.h"

int active = 0;

void initPortE(void) {
	S32_NVIC->ISER[63/32]|=1<<(63%32);
}

void PORTE_IRQHandler (void){
	if ((PTE -> PDIR & (1<<15)) == (1<<15)){
		active = 1;
	}
	if (((PTE -> PDIR & (1<<14)) == (1<<14)) && ((PTE -> PDIR & (1<<15)) != (1<<15))){
		active = 0;
	}

	if (active == 1){
		PTD->PDOR=(0<<0)+(0<<15)+(0<<16);   				//Led Blanco
		PTC->PDDR|=(1<<12) + (1<<13);
		PTE->PDDR|=(1<<7);
		PTD -> PCOR = (1<<11) + (1<<5) + (1<<10) + (1<<3);  //Parar Motores
		PTA->PCOR |= (1<<11) + (1<<17);  					//Parar Actuador
		PORTE->PCR[14]|=(1<<24);
	}else {
		PORTE->PCR[15]|=(1<<24);
	}
}
