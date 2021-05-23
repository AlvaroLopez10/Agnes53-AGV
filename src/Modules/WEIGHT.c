/*
 * WEIGHT.c
 *
 *  Created on: 07/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "WEIGHT.h"
#include "../Functions/MANUAL.h"

float CONST_A = 0.0000100043;
float CONST_B = 84.7903583;
long OFFSET = 0;
float weight = 0;
double weight_value;

unsigned long readCount(void){
	unsigned long count;
	unsigned int i;

	PTB -> PCOR = (1<<15);									//Apagar clock
	count=0;

	while((PTB -> PDIR & (1<<14)) == (1<<14));

	for (i=0;i<24;i++){
		PTB -> PSOR = (1<<15);								//Prender Clock
		count=count<<1;
		PTB -> PCOR = (1<<15);								//Apagar clock
		if((PTB -> PDIR & (1<<14)) == (1<<14)) count++;
	}

	PTB -> PSOR = (1<<15);									//Prender Clock
	count=count^0x800000;
	PTB -> PCOR = (1<<15);									//Apagar clock

	return(count);
}

unsigned long readAverage(int times){
	unsigned long sum = 0;
	unsigned int i;
	for (i = 0; i < times; i++) {
		sum += readCount();
	}
	return sum / times;
}

double getValue(int times){
	return readAverage(times) - OFFSET;
}

float getUnits(int times){
	return -(CONST_A * getValue(times)) + CONST_B;
}

void tare(int times){
	double sum = readAverage(times);
	OFFSET = sum;
}

void getWeight(void){
	weight = getUnits(1);
	//weight_value = getValue(20);
}


