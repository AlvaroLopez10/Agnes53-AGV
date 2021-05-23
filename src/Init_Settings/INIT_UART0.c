/*
 * INIT_UART0.c
 *
 *  Created on: 11/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT_UART0.h"

unsigned int j=0;
unsigned long letra_p = 0;
unsigned char TEMPORAL;
unsigned char arr_rasp[3];
unsigned char arr_message[]={'C'};
int uart0_interrupt=0;

void initUART0(void) {

	PCC -> PCCn[PCC_LPUART0_INDEX] = (3<<24);  	//Habilitar Reloj UART, se habilita CGC bit 30 y en PCS bit 24-26 conf 011 para elegir FIRCDIV2 (C29-646), ver diagramas (C27-536) y (C27-546)
	PCC -> PCCn[PCC_LPUART0_INDEX] |= (1<<30);  	//Habilitar Reloj UART, se habilita CGC bit 30 y en PCS bit 24-26 conf 011 para elegir FIRCDIV2 (C29-646), ver diagramas (C27-536) y (C27-546)
	LPUART0 -> BAUD = 312;
	LPUART0 -> CTRL = (3<<18) +(1<<21) + (1<<23);					//(C51-1551) */

	S32_NVIC -> ISER[31/32] |= 1<<(31 % 32);				//Habilita a la interrupcion del UART. 31 -- ID de la interrupcion (Excel). |= Asegurarse que no cambien los demas bits
}

void LPUART0_RxTx_IRQHandler (void){
	uart0_interrupt=1;
	if (((LPUART0->STAT & (1<<21))!=0)){
		TEMPORAL = LPUART0->DATA;
		arr_rasp[j] = TEMPORAL;
		j++;
		if(j==3){
			j=0;
		}
	}
	if ((LPUART0->STAT & (1<<23))!=0) {
		LPUART0->CTRL&=~(1<<23);
	}
	uart0_interrupt=0;
}
