/*
 * INIT_UART2.c
 *
 *  Created on: 06/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT_UART2.h"
#include "../Modules/MECANISM.h"
#include "../Functions/MANUAL.h"

unsigned char arr_commands[][25]={
		"AT+RST\r\n",
		"AT+CIPMUX=1\r\n",
		"AT+CIPSERVER=1,80\r\n"};
int a=0;
int b=0;
int i=0;
unsigned char arr_input[20];	//datos que ir recibiendo a partir del GET hasta el dato mandado
unsigned char arr_wifi_data[15]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned char ready=0;
unsigned char counter=0;
unsigned char letter=0;
int h = 0;
int uart2_interrupt=0;

void initUART2 (void){
	PCC->PCCn[PCC_LPUART2_INDEX]=3<<24;				    //selecciona el clock FIRCDIV
	PCC->PCCn[PCC_LPUART2_INDEX]|=1<<30;				//hab comunicacion con la UART
	LPUART2->BAUD=26; 									//se pone el valor del SBR, controla la velocidad de comunicacion
	LPUART2->CTRL=(3<<18)+(1<<23)+(1<<21);

	S32_NVIC->ISER[35/32]|=(1<<(35%32));
}

void assignData (void){
	int p;
	for (p=0; p<=14;p++){
		arr_wifi_data[p]=arr_input[p+5];
	}
	p=0;
}

void sendCommand (int index){
	LPUART2->DATA=arr_commands[index][letter++];
	if(arr_commands[index][letter]==0){
		LPUART2->CTRL&=~(1<<23);
	    letter=0;
	    i++;
	}
}

void LPUART2_RxTx_IRQHandler (void){
	uart2_interrupt=1;
	if ((LPUART2->STAT&(1<<21))!=0){
		if (ready==0){
			unsigned char tmp_ok;
			tmp_ok=LPUART2->DATA;
			arr_input[8]=tmp_ok;

			if  ((arr_input[0]=='r')&&(arr_input[1]=='e')&&(arr_input[2]=='a')&& (arr_input[3]=='d')&&(arr_input[4]=='y')){
				ready=1;
				LPUART2->CTRL|=(1<<23);
				counter=i;
			}else {
				do{arr_input[a]=arr_input[a+1];
					a++;
				}while(a<9);
					a=0;
			} //else ready
		} else if (ready==1){
			unsigned char tmp_ok;
			tmp_ok=LPUART2->DATA;
			arr_input[8]=tmp_ok;

			if ((arr_input[0]=='O')&& (arr_input[1]=='K')) {
				LPUART2->CTRL|=(1<<23);
				counter=i;


				if (counter==3){
					LPUART2->CTRL&=~(1<<23);
					PTC->PDDR|=(1<<12) + (0<<13);
					PTE->PDDR|=(1<<7);
					PTD->PDOR=(1<<15)+(0<<16)+(0<<0);
					ready=2;
				}

			}else {
				do{
					arr_input[a]=arr_input[a+1];
					a++;
				}while(a<9);
					a=0;
			} //else ok

		} else if (ready==2){
			unsigned char tmp_reference;
			tmp_reference = LPUART2->DATA;
			arr_input[20] = tmp_reference;
			h++;

			if ((arr_input[0]=='G') && (arr_input[1]=='E') && (arr_input[2]=='T') && (arr_input[3]==' ') && (arr_input[4]=='/')){
				arr_input[0]=0;
				assignData();
				LPUART2->CTRL|=(1<<23);
			}else{
				do{arr_input[b]=arr_input[b+1];
					b++;
				}while(b<21);
					b=0;
			} //else get
		} //ready 2
	}else{ //else STAT21

		if ((LPUART2->STAT&(1<<23))!=0){
			sendCommand(i);
		}else{
			LPUART2->CTRL&=~(1<<23);
		} //else bANDERA off
	} //else STAT21
	uart2_interrupt=0;
}
