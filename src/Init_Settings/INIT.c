/*
 * INIT.c
 *
 *  Created on: 06/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT.h"

void init(void){

	SCG->SIRCDIV=(1<<8) + 1;
	SCG->FIRCDIV=(1<<8) + 13;									//LPUART2 prescaler de 1 FIRCDIV=48MHz

	//LPTMR0
	PCC->PCCn[PCC_LPTMR0_INDEX] |= (1<<30);

	//LPIT
	PCC->PCCn[PCC_LPIT_INDEX] = 2<<24;    				 				/* (Z.546)+ ASSIGN(Z.618)Clock Src = 2 (SIRCDIV2_CLK)*/
	PCC->PCCn[PCC_LPIT_INDEX] |= 1<<30; 					 				/* Enable clk to LPIT0 regs (Z.1371)*/
	LPIT0->MCR = 0x00000001;

	//PORTS
	PCC->PCCn[PCC_PORTC_INDEX] |= (1<<30);
	PCC->PCCn[PCC_PORTA_INDEX] |= (1<<30);					//Habilitar Reloj Puerto D, solo se habilita CGC bit 30 (C29-628)
	PCC->PCCn[PCC_PORTD_INDEX] |= (1<<30);					//Habilitar Reloj Puerto D, solo se habilita CGC bit 30 (C29-628)
	PCC->PCCn[PCC_PORTB_INDEX] |= (1<<30);					//Habilitar Reloj Puerto D, solo se habilita CGC bit 30 (C29-628)
	PCC->PCCn[PCC_PORTE_INDEX] |= (1<<30);					//Habilitar Reloj Puerto D, solo se habilita CGC bit 30 (C29-628)

	//LEDS
    PORTD->PCR[15]=1<<8; 					//LEDS ROJO declara pin 15 del puerto C como  GPIO
    PORTD->PCR[0]=1<<8; 					//LED AZULdeclara pin 0 del puerto C como  GPIO
    PORTD->PCR[16]=1<<8; 					//LED VERDE declara pin 16 del puerto C como  GPIO

    //LINEA LEDS
    PORTC->PCR[12]=(1<<8);					//VERDE
    PORTC->PCR[13]=(1<<8);					//ROJO
    PORTE->PCR[7]=(1<<8);					//AZUL

    //MOTORES
    PORTD -> PCR[5] = 0x00000100;           //Direccion A Motor 1 en Puerto D Bit 5 (Guia)(C12-198)
    PORTD -> PCR[3] = 0x00000100;			//Direccion B Motor 1 en Puerto D Bit 3 (Guia)(C29-633)
    PORTD -> PCR[11] = 0x00000100;          //Direccion A Motor 2 en Puerto D Bit 11 (Guia)(C12-198)
    PORTD -> PCR[10] = 0x00000100;          //Direccion B Motor 2 en Puerto D Bit 10 (Guia)(C12-198)

    //ACTUADOR
	PORTA->PCR[11]=(1<<8);
	PORTA->PCR[17]=(1<<8);

	//INFRARROJO
	PORTA->PCR[0]=(1<<8);
	PORTA->PCR[7]=(1<<8);

    //WEIGHT
	PORTB -> PCR[14] = (1<<8);								//Habilitar Puerto C GPIO DATA
	PORTB -> PCR[15] = (1<<8);								//Habilitar Puerto C GPIO CLOCK

	//SWITCH MECANISM
	PORTD->PCR[9]=(1<<8) + (10<<16);
	PORTD->PCR[2]=(1<<8) + (10<<16);

	//BOTONES
	PORTE->PCR[15]=(1<<8) + (11<<16); 					//Boton Paro
	PORTE->PCR[14]=(1<<8) + (10<<16); 					//Reset

	//ALARM
	//PORTE->PCR[13]=(1<<8);

	//BUZZER
	PORTE->PCR[16]=(1<<8);

	//SALIDAS PUERTO A
	PTA->PDDR|=(1<<17)+(1<<11); 									//declara pin 0,15,16 del puerto C como  salidas
	PTA->PSOR |= (1<<11) + (1<<17);										//Iniciar con los pines del motor apagados (C13-213)

    //SALIDAS PUERTO B
	PTB -> PDDR = (1<<15);                    	 			//Configurar pin 5 como salida clock

	//SALIDAS PUERTO C
	PTC->PDDR|=(1<<12);				//VERDE
	PTC->PDDR|=(1<<13);				//ROJO

	//SALIDAS PUERTO D
    PTD -> PDDR |=0x00018001; 									//declara pin 0,15,16 del puerto C como  salidas
	PTD -> PDOR |= 1;										//Iniciar con los pines del motor apagados (C13-213)
	PTD->PDOR=(0<<0)+(0<<15)+(0<<16);
	PTD -> PDDR |= (1<<11) + (1<<10) + (1<<5) + (1<<3);      //Configurar pin 3,5,10,11 como salidas con "1" confg 011 3<<5 + 0110 3<<9 (C13-218)
	PTD->PSOR |= (1<<3) + (1<<10) + (1<<5) + (1<<11);

	//SALIDAS PUERTO E
	PTE->PDDR|=(1<<16); 									//declara pin 14 salida
	PTE->PCOR |= (1<<16);										//Iniciar con los pines apagados (C13-213)
	PTE->PDDR|=(1<<7);				//AZUL
	//PTE->PDDR|=(1<<13); 									//declara pin 14 salida
	//PTE->PCOR |= (1<<13);										//Iniciar con los pines apagados (C13-213)

    //LPUART2 WIFI
    PORTD->PCR[7]=2<<8;									//declara pin 6 puerto C como SDA UART Tx
    PORTD->PCR[6]=2<<8;									//declara pin 6 puerto C como SDA UART Rx

    //FTM3 MOTORES
    PORTB->PCR[8] = (2<<8);								//PWM Motor 1 en Puerto A Bit 3(Guia)(C12-198)
    PORTB->PCR[10] = (2<<8);							//PWM Motor 1 en Puerto B Bit 8 (Guia)(C12-198)

    //FTM3 ACTUADOR
	PORTB->PCR[11]=(2<<8);  //FLEX PWM

	//FTM0 ENCODERS
 	PORTB->PCR[12] = (2<<8); 							//PB12 como FTM0_CH0
 	PORTB->PCR[13] = (2<<8);							//PB13 como FTM0_CH1

    //LPUART0 PIXY
    PORTB -> PCR[0] = (2<<8);								//Habilitar Puerto B como UART con el MUX bit 8-10 confg 010 2<<8 (C12-198 Excel). Guía rápida (Receiver)
    PORTB -> PCR[1] = (2<<8);								//Habilitar Puerto B como UART con el MUX bit 8-10 confg 010 2<<8 (C12-198 Excel). Guía rápida (Transmiter)

    //I2C
    PORTA->PCR[2] |= 3<<8;							//PIN2 Puerto A SDA (excel I/O)
    PORTA->PCR[3] |= 3<<8;							//PIN3 Puerto A SCL (excel)
}
