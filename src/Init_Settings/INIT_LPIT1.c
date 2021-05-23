/*
 * INIT_LPIT1.c
 *
 *  Created on: 07/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT_LPIT0.h"
#include "INIT_LPIT1.h"
#include "../Functions/SEMIAUTOMATICO.h"

void initLPIT1 (void){

	LPIT0->MIER = 1<<1;    										/* TIE0=1: Timer Interrupt Enabled fot Chan 0 */
	LPIT0->TMR[1].TVAL = 1000000;     									/* Chan 0 Timeout period: 5M clocks */
	LPIT0->TMR[1].TCTRL = 0x00000001;  									/* T_EN=1: Timer channel is enabled */

	S32_NVIC->ISER[49/32] = 1 << (49 % 32); 								/* IRQ49-LPIT0 ch1: enable IRQ */
}

void LPIT0_Ch1_IRQHandler (void){

	LPIT0->MSR |= 1<<1;
    semiautomatico();
}
