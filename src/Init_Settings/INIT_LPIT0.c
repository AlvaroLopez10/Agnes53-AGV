/*
 * INIT_LPIT0.c
 *
 *  Created on: 07/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT_LPIT0.h"
#include "INIT_LPIT1.h"
#include "../Functions/MANUAL.h"

int k = 0;
extern unsigned int Arrived; //0 No a llegado //Acaba de llegar
extern float peso;

void initLPIT0 (void){
	LPIT0->MIER = 0x00000001;    										/* TIE0=1: Timer Interrupt Enabled fot Chan 0 */
	LPIT0->TMR[0].TVAL = 4000000;     									/* Chan 0 Timeout period: 5M clocks */
	LPIT0->TMR[0].TCTRL = 0x00000001;  									/* T_EN=1: Timer channel is enabled */

	S32_NVIC->ISER[48/32] = 1 << (48 % 32); 								/* IRQ48-LPIT0 ch0: enable IRQ */
}

void LPIT0_Ch0_IRQHandler (void){
	LPIT0->MSR |= 1<<0;  												/* Clear LPIT0 timer flag 0 */
    k++;
    manual();
	LPUART2->CTRL|=(1<<21);
}

