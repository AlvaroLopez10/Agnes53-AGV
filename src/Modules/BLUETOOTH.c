/*
 * BLUETOOTH.c
 *
 *  Created on: 15/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "BLUETOOTH.h"
#include "../Init_Settings/INIT_LPIT1.h"

unsigned char arr_sensors[33]={"+AYYYY+BYYYY+XYYY+DYYY+EYYYY+FYYY"}; // este es el arreglo qye hay que estar modificando desde la lectura de cada sensor, pero solo modificar la seccion correspondiente a cada sensor
//unsigned char arr_sensors[4]={"+A1C"};
int counter_send=0;
unsigned int letter_bt=0;

void sensorCurrent(int number){
	int i;
	for(i=5; i>1; i--){
		arr_sensors[i]=(number%10)+0x30;
		number=number/10;
	}
}

void sensorVoltage(int number){
	int i;
	for(i=11; i>7; i--){
		arr_sensors[i]=(number%10)+0x30;
		number=number/10;
	}
}

void sensorRev1(int number){
	int i;
	for(i=16; i>13; i--){
		arr_sensors[i]=(number%10)+0x30;
		number=number/10;
	}
}

void sensorRev2(int number){
	int i;
	for(i=21; i>18; i--){
		arr_sensors[i]=(number%10)+0x30;
		number=number/10;
	}
}

void sensorVelocity(int number){
	int i;
	for(i=27; i>23; i--){
		arr_sensors[i]=(number%10)+0x30;
		number=number/10;
	}
}

void sensorOrientation(int number){
	int i;
	for(i=32; i>29; i--){
		arr_sensors[i]=(number%10)+0x30;
		number=number/10;
	}
}

void sendBluetooth (void){
	counter_send++;
	do{
		 do{}while ((LPUART0->STAT & (1<<23))==0);
		 LPUART0->DATA=arr_sensors[letter_bt++];
	}while (arr_sensors[letter_bt]!=0);
	letter_bt = 0;
}
