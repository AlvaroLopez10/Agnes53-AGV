/*
 * SEMIAUTOMATICO.c
 *
 *  Created on: 08/11/2019
 *      Author: alvar
 */
#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "SEMIAUTOMATICO.h"
#include "LINE_TRACKER.h"
#include "../Init_Settings/INIT_UART0.h"
#include "../Init_Settings/INIT_UART2.h"
#include "../Init_Settings/INIT_LPIT0.h"
#include "../Init_Settings/INIT_LPIT1.h"
#include "../Init_Settings/INIT_FTM.h"
#include "../Init_Settings/INIT_FTM0.h"
#include "../Init_Settings/INIT_ADC0.h"
#include "../Init_Settings/INIT_I2C.h"
#include "../Modules/BLUETOOTH.h"

extern unsigned char arr_rasp[3];
extern unsigned char arr_wifi_data[15];
unsigned char arr_sequence[12];
extern float rpm_0;
extern float rpm_1;
extern float vel_0;
extern float vel_1;
extern unsigned int pwm_right;
extern unsigned int pwm_left;
unsigned int station=0;
unsigned int error_time=0;
unsigned int station_time = 0;
unsigned int tmp_color=0; //0
int filter_tx = 0;
int alarm_leds = 0;

void resetSequence(void){
	int reset_seq;
	for(reset_seq=0; reset_seq<=11;reset_seq++){
		arr_sequence[reset_seq]='S';
	}
	reset_seq=0;
	arr_wifi_data[0] = 'M';
	arr_wifi_data[1] = 'A';
	arr_wifi_data[2] = 'N';
	arr_wifi_data[3] = 'S';
}

void motorsOff (void){
	PTD->PDOR=(0<<0)+(0<<15)+(0<<16);   //Led Blanco
	PTC->PDDR|=(1<<12) + (1<<13);
	PTE->PDDR|=(1<<7);
	PTD -> PSOR = (1<<11) + (1<<5) + (1<<10) + (1<<3);
}

void alarmOn (void){
	PTD -> PSOR = (1<<11) + (1<<5) + (1<<10) + (1<<3);
	alarm_leds++;
	if (alarm_leds < 8) {
		PTE->PSOR |= (1<<16);
		//PTE->PSOR |= (1<<13);
		PTD->PDOR=(0<<0)+(0<<15)+(0<<16);   //Led Blanco
		PTC->PDDR|=(1<<12) + (1<<13);
		PTE->PDDR|=(1<<7);
	}else if (alarm_leds < 16){
		PTE->PCOR |= (1<<16);
		//PTE->PCOR |= (1<<13);
		PTD->PDOR=(0<<0)+(0<<15)+(0<<16);   //Led Blanco
		PTC->PDDR|=(1<<12) + (1<<13);
		PTE->PDDR|=(1<<7);
		if (alarm_leds == 15){
			alarm_leds = 0;
		}
	}
}

void followStation (unsigned char direccion){
	if(direccion == 'F'){																//Front
		PTD->PDOR=(0<<0)+(1<<15)+(1<<16);  //Led Azul
		PTC->PDDR|=(0<<12) + (0<<13);
		PTE->PDDR|=(1<<7);
		PWM(75,70,100);
		PTD -> PCOR = (1<<10) + (1<<5);						//Encender Direccion A Motor 1, Direccion A Motor 2
		PTD -> PSOR = (1<<11) + (1<<3);						//Apagar Direccion B Motor 1, Direccion B Motor 2

	}
	if(direccion == 'R'){
		PTD->PDOR=(1<<0)+(0<<15)+(1<<16);	//Led Rojo												//Right
		PTC->PDDR|=(0<<12) + (1<<13);
		PTE->PDDR|=(0<<7);
		PWM(100,60,100);
		PTD -> PCOR = (1<<10);						//Encender Direccion A Motor 1, Direccion B Motor 2
		PTD -> PSOR = (1<<11) + (1<<5) + (1<<3);						//Apagar Direccion B Motor 1, Direccion A Motor 2

	}
	if(direccion == 'L'){																//Left
		PTD->PDOR=(1<<0)+(1<<15)+(0<<16);   //Led Verde
		PTC->PDDR|=(1<<12) + (0<<13);
		PTE->PDDR|=(0<<7);
		PWM(70,100,100);
		PTD -> PCOR = (1<<5);						//Encender Direccion B Motor 1, Direccion A Motor 2
		PTD -> PSOR = (1<<10) + (1<<3)+(1<<11);						//Apagar Direccion A Motor 1, Direccion B Motor 2

	}
	if(direccion == 'S'){															//Stop
		motorsOff();
	}
}

void followSequence(void) {
	if((arr_sequence[station]!='S')){
		if(arr_rasp[0]==1){
			//Seguir línea
			if(tmp_color==2){
		    	station_time++;
		    	if (station_time < 16){
			    	followStation(arr_sequence[station]);
		    	}else {
		    		station++;
		    		tmp_color=1;
		    		station_time=0;
		    	}
	    	}else if (tmp_color==1) {
				if (filter_tx == 0) {
			    	PTD->PDOR=(0<<0)+(0<<15)+(1<<16); //Led Rosa
					PTC->PDDR|=(0<<12) + (1<<13);
					PTE->PDDR|=(1<<7);
					PWM(pwm_right, pwm_left,100);
					PTD -> PCOR = (1<<10) + (1<<5);						//Encender Direccion A Motor 1, Direccion A Motor 2
					PTD -> PSOR = (1<<11) + (1<<3);						//Apagar Direccion B Motor 1, Direccion B Motor 2
				}else {
					motorsOff();
				}
	    	}
	    } //Seguir Linea
	    if(arr_rasp[0]==2){
	    	//Alto
	    	tmp_color=2;
	    	followStation(arr_sequence[station]);
	    } //Alto
	    if(arr_rasp[0]==0){
	    	if(tmp_color==1){
	    		//No detecta color
	    		error_time++;
				if (filter_tx == 0) {
			    	PTD->PDOR=(0<<0)+(0<<15)+(1<<16); //Led Rosa
					PTC->PDDR|=(0<<12) + (1<<13);
					PTE->PDDR|=(1<<7);
					PTD -> PCOR = (1<<10) + (1<<5);						//Encender Direccion A Motor 1, Direccion A Motor 2
					PTD -> PSOR = (1<<11) + (1<<3);						//Apagar Direccion B Motor 1, Direccion B Motor 2
				}else {
					motorsOff();
				}
	    		/* if(error_time==1000000){
	    			tmp_color=0;
	    			motorsOff();
	    			error_time=0;
	    		} //No detectó línea por 5 segundos */
	    	} else if (tmp_color==2) {
		    	followStation(arr_sequence[station]);
	    	} else {
    			motorsOff();
    			error_time=0;
	    	}
	    } //No detecta color
	} //if !='S'
	if(arr_sequence[station]=='S'){
		if((arr_rasp[0]==1)&&(tmp_color==1)){
			//Seguir Linea
			if (filter_tx == 0) {
		    	PTD->PDOR=(0<<0)+(0<<15)+(1<<16); //Led Rosa
				PTC->PDDR|=(0<<12) + (1<<13);
				PTE->PDDR|=(1<<7);
				PWM(pwm_right, pwm_left,100);
				PTD -> PCOR = (1<<10) + (1<<5);						//Encender Direccion A Motor 1, Direccion A Motor 2
				PTD -> PSOR = (1<<11) + (1<<3);						//Apagar Direccion B Motor 1, Direccion B Motor 2
			}else {
				motorsOff();
			}
	    }
		if(arr_rasp[0]==2){
			//Finish
	    	PTD->PDOR=(0<<0)+(0<<15)+(0<<16);	//Led Blanco
	    	motorsOff();
	    	station=0;
	    	tmp_color=0;
	    	resetSequence();
	        LPIT0->MIER = 0<<1;
	        initLPIT0();
	    	LPUART2->CTRL=(3<<18)+(1<<23)+(1<<21);
	    }
	}
}

void semiautomatico(void){

	if (filter_tx == 0){
    	LPUART0->DATA='C';
    	filter_tx++;
	}else {
		filter_tx = 0;
    	readCurrent();
    	sensorRev1(rpm_0);
    	sensorRev2(rpm_1);
    	sensorVelocity((vel_0+vel_1)*1000/2);
    	readOrientation();
    	sendBluetooth();
    }

	if (((PTA -> PDIR & (1<<7)) == (1<<7)) && ((PTA -> PDIR & (1<<0)) == (1<<0))){
		PTE->PCOR |= (1<<16);
		//PTE->PCOR |= (1<<13);
	    if((arr_wifi_data[0]=='A')&&(arr_wifi_data[1]=='U')&&(arr_wifi_data[2]=='T')){

	    	if (station == 0){
	        	motorsOff();
	        	int p;
	        	for (p=0; p<=11;p++){
	            	arr_sequence[p] = arr_wifi_data[p+3];
	        	}
	        	p=0;
	    	}

	    	lineTracker();
	    	followSequence();

	    }else {
	    	if (station == 0) {
	            LPIT0->MIER = 0<<1;
	            initLPIT0();
	    	}else {
	    		followSequence();
	    	}
	    }
	} else {
		alarmOn();
	}
}
