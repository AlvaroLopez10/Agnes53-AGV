/*
 * INIT_ADC0.c
 *
 *  Created on: 18/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT_ADC0.h"
#include "INIT_LPIT1.h"
#include "../Modules/BLUETOOTH.h"

float value_ADC;
float voltage;
float current;
float RESISTANCE=10;
int final_voltage;
int final_current;

void initADC0(void){
    PCC->PCCn[PCC_ADC0_INDEX]=(2<<24);
    PCC->PCCn[PCC_ADC0_INDEX]|=(1<<30);

    ADC0->CFG1=2<<2;
}

void readCurrent (void){
    ADC0->SC1[0]=1;
	value_ADC = ADC0->R[0];
	voltage = ((value_ADC*5/1023)-2.5);
	current = (13.654*voltage)-1.0044;
	if (current < 0) {
		current = -current;
	}
	final_voltage = current*1000*RESISTANCE*2;
	final_current = current*1000*2;
    sensorCurrent(final_current);
    sensorVoltage(final_voltage);
}




