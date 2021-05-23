/*
 * MANUAL.c
 *
 *  Created on: 07/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "MANUAL.h"
#include "../Init_Settings/INIT_UART2.h"
#include "../Init_Settings/INIT_LPIT0.h"
#include "../Init_Settings/INIT_LPIT1.h"
#include "../Init_Settings/INIT_FTM.h"
#include "../Modules/MECANISM.h"
#include "../Modules/WEIGHT.h"

extern unsigned char arr_wifi_data[15];
unsigned char command_manual;
extern unsigned int arrived; //0 No a llegado //Acaba de llegar
extern unsigned int limit; //0 Abajo //1 Arriba
extern unsigned int enable;
extern float weight;
int beast_time = 0;
int party_time = 0;
int dance_time = 0;

void moveManual(void){
	if(command_manual == 'F'){
			PWM(65,60,0);															//Front
			PTD->PDOR=(0<<0)+(1<<15)+(1<<16);
			PTC->PDDR|=(0<<12) + (0<<13);
			PTE->PDDR|=(1<<7);
			PTD -> PSOR = (1<<11) + (1<<3);						//Encender Direccion A Motor 1, Direccion A Motor 2
			PTD -> PCOR = (1<<10) + (1<<5);						//Apagar Direccion B Motor 1, Direccion B Motor 2
		} if(command_manual == 'R'){
			PWM(55,60,0);
			PTD->PDOR=(1<<0)+(0<<15)+(1<<16);					//Right
			PTC->PDDR|=(0<<12) + (1<<13);
			PTE->PDDR|=(0<<7);
			PTD -> PCOR = (1<<10) + (1<<3);						//Encender Direccion A Motor 1, Direccion B Motor 2
			PTD -> PSOR = (1<<11) + (1<<5);						//Apagar Direccion B Motor 1, Direccion A Motor 2

		} if(command_manual == 'L'){
			PWM(65,55,0);																	//Left
			PTD->PDOR=(1<<0)+(1<<15)+(0<<16);
			PTC->PDDR|=(1<<12) + (0<<13);
			PTE->PDDR|=(0<<7);
			PTD -> PCOR = (1<<11) + (1<<5);						//Encender Direccion B Motor 1, Direccion A Motor 2
			PTD -> PSOR = (1<<10) + (1<<3);						//Apagar Direccion A Motor 1, Direccion B Motor 2
		}
		if(command_manual == 'B'){
			PWM(60,55,0);																			//Back
			PTD->PDOR=(1<<0)+(0<<15)+(0<<16);
			PTC->PDDR|=(1<<12) + (1<<13);
			PTE->PDDR|=(0<<7);
			PTD -> PSOR = (1<<10) + (1<<5);						//Encender Direccion B Motor 1, Direccion A Motor 2
			PTD -> PCOR = (1<<11) + (1<<3);						//Apagar Direccion A Motor 1, Direccion B Motor 2
		}
		if(command_manual == 'S'){															//Stop
			PTE->PCOR |= (1<<16);
			PTD->PDOR=(0<<0)+(0<<15)+(0<<16);
			PTC->PDDR|=(1<<12) + (1<<13);
			PTE->PDDR|=(1<<7);
			PTD -> PSOR = (1<<10) + (1<<5) + (1<<11) + (1<<3);
		}
		if(command_manual == 'X'){															//Beast Mode
			PWM(60,100,0);
			//PTD -> PCOR = (1<<11) + (1<<5);						//Encender Direccion B Motor 1, Direccion A Motor 2
			//PTD -> PSOR = (1<<10) + (1<<3);						//Apagar Direccion A Motor 1, Direccion B Motor 2
			if (beast_time == 0) {
				PTD->PDOR=(1<<0)+(0<<15)+(1<<16);					//Right
				PTC->PDDR|=(0<<12) + (1<<13);
				PTE->PDDR|=(0<<7);
				beast_time++;
			}else {
				PTD->PDOR=(0<<0)+(0<<15)+(0<<16);
				PTC->PDDR|=(1<<12) + (1<<13);
				PTE->PDDR|=(1<<7);
				beast_time = 0;
			}
			PTD -> PCOR = (1<<11) + (1<<5);						//Encender Direccion B Motor 1, Direccion A Motor 2
			PTD -> PSOR = (1<<10) + (1<<3);						//Apagar Direccion A Motor 1, Direccion B Motor 2

		}
		if(command_manual == 'P'){
			if (party_time == 0) {
				//AZUL
				PTD->PDOR=(0<<0)+(1<<15)+(1<<16);
				PTC->PDDR|=(0<<12) + (0<<13);
				PTE->PDDR|=(1<<7);
				party_time++;
			}else if (party_time == 1) {
				//ROJO
				PTD->PDOR=(1<<0)+(0<<15)+(1<<16);
				PTC->PDDR|=(0<<12) + (1<<13);
				PTE->PDDR|=(0<<7);
				party_time++;
			}else {
				//VERDE
				PTD->PDOR=(1<<0)+(1<<15)+(0<<16);
				PTC->PDDR|=(1<<12) + (0<<13);
				PTE->PDDR|=(0<<7);
				party_time=0;
			}														//Party Mode
			if (dance_time == 0) {
				PTE->PCOR |= (1<<16);
				PWM(70,65,0);
				PTD -> PSOR = (1<<11) + (1<<3);
				PTD -> PCOR = (1<<10) + (1<<5);
				dance_time++;
			}else {
				PTE->PSOR |= (1<<16);
				PWM(70,65,0);
				PTD -> PSOR = (1<<10) + (1<<5);
				PTD -> PCOR = (1<<11) + (1<<3);
				dance_time = 0;
			}
		}
}

void controlMecanism(void){
	//getWeight();
    if (weight < 10){
    	if (command_manual=='W' || command_manual=='M') {
    		mecanism();
    	} else if (enable == 1){
    		if (limit == 0) {
    			command_manual = 'M';
    		} else {
    			command_manual = 'W';
    		}
    		mecanism();
    	}
    }else{
    	mecanismStop();
    }
	if (arrived == 1 && limit == 0){
		moveManual();
	}
}

void manual(void){

	if((arr_wifi_data[0]=='M')&&(arr_wifi_data[1]=='A')&&(arr_wifi_data[2]=='N')){

		command_manual=arr_wifi_data[3];
		controlMecanism();

	}
	else if (arr_wifi_data[0] != 0){
		if(arrived == 1 && limit == 0){
		    LPIT0->MIER = 0<<0;
		    initLPIT1();
		} else if (enable == 1){
			controlMecanism();
		}
	}
}

