/*
 * INIT_FTM0.c
 *
 *  Created on: 15/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT_FTM0.h"
#include "../Modules/BLUETOOTH.h"

unsigned long revolutions_0=0;
unsigned long revolutions_1=0;
float FTM0_CH0_period=0.0;
float FTM0_CH1_period=0.0;
unsigned short old_time_0=0;
unsigned short old_time_1=0;
unsigned short new_time_0=0;
unsigned short new_time_1=0;
unsigned short overflow_0=0;
unsigned short overflow_1=0;
float rpm_0=0.0;
float rpm_1=0.0;
float vel_0=0.0;
float vel_1=0.0;
int ftm_interrupt = 0;

void initFTM0 (void){

 	PCC->PCCn[PCC_FTM0_INDEX]=3<<24;			//Seleciconar FIRCDIV
 	PCC->PCCn[PCC_FTM0_INDEX]|=1<<30;

 	S32_NVIC->ISER[99/32]=(1<<(99%32)); 		//Enable FTM0 interrupt
 	S32_NVIC->ISER[104/32]=(1<<(104%32)); 		//Enable FTM0 overflow interrupt


 	FTM0->CONTROLS[0].CnSC = (1<<6)+(3<<2); 	//1<<2 para seleccionar flanco subida y bajada p.1266, channel interrupt enable
 	FTM0->CONTROLS[1].CnSC = (1<<6)+(3<<2);

 	FTM0->SC = (1<<8)+(3<<3)+7;					//MUX PCC, External clock, 3 para Prescaler en 8 FTM clock: 1MHz, (1<<8) habilitar overflow interrupt
}

void FTM0_Ch0_Ch1_IRQHandler(void)
{
	ftm_interrupt = 1;
	if ((FTM0->CONTROLS[0].CnSC & (1<<7)) && (FTM0->CONTROLS[0].CnSC & (1<<6))){
		(void)FTM0->CONTROLS[0].CnSC; 				//leer registro paso 1 para borrar flag, da igual lo que se lea
		FTM0->CONTROLS[0].CnSC&=~(1<<7);			//&= escribir 0 en ese bit, mascara para apagar bit 7, paso 2 para borrar flag
		new_time_0=FTM0->CONTROLS[0].CnV;

		if(new_time_0>old_time_0){
			revolutions_0=(overflow_0*65536)+new_time_0-old_time_0;
			overflow_0=0;
		}
		else{
			revolutions_0=((overflow_0-1)*65536)+new_time_0-old_time_0;
			overflow_0=0;
		}
		old_time_0=FTM0->CONTROLS[0].CnV;

		FTM0_CH0_period=((revolutions_0*0.000021333333333)*4);
		rpm_0 = (0.1/FTM0_CH0_period);
		vel_0=(0.00797964534013)*rpm_0;   		//convierto a radianes y multiplico por el radio (3 in);
		revolutions_0=0;
	}

	if ((FTM0->CONTROLS[1].CnSC & (1<<7)) && (FTM0->CONTROLS[1].CnSC & (1<<6))){
		(void)FTM0->CONTROLS[1].CnSC; 			//leer registro paso 1 para borrar flag, da igual lo que se lea
		FTM0->CONTROLS[1].CnSC&=~(1<<7);		//&= escribir 0 en ese bit, mascara para apagar bit 7, paso 2 para borrar flag
		new_time_1=FTM0->CONTROLS[1].CnV;

		if(new_time_1>old_time_1){
			revolutions_1=(overflow_1*65536)+new_time_1-old_time_1;
			overflow_1=0;
		}
		else{
			revolutions_1=((overflow_1-1)*65536)+new_time_1-old_time_1;
			overflow_1=0;
		}
		old_time_1=FTM0->CONTROLS[1].CnV;

		FTM0_CH1_period=(revolutions_1*0.00017066666666666);
		rpm_1 = (0.1/FTM0_CH1_period);
		vel_1=(0.00797964534013)*rpm_1;   		//convierto a radianes y multiplico por el radio (3 in);
		revolutions_1=0;
	}
	ftm_interrupt = 0;
}

void FTM0_Ovf_Reload_IRQHandler (void){
	(void)FTM0->SC;			 	//leer registro paso 1 para borrar flag, da igual lo que se lea
	FTM0->SC&=~(1<<9);			//&= escribir 0 en ese bit, mascara para apagar bit 9, paso 2 para borrar flag
	overflow_0++;
	overflow_1++;
}
