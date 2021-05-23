/*
 * INIT_FTM.c
 *
 *  Created on: 07/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "INIT_FTM.h"
#include "../Modules/MECANISM.h"
#include "../Functions/MANUAL.h"

void initFTM3(void){
	PCC->PCCn[PCC_FTM3_INDEX] |= (2<<24);							//Elegir SIRCDIV1 en PCS bit 24-26 confg 010 (C29-603), ver diagramas (C27-536) y (C27-550)
	PCC->PCCn[PCC_FTM3_INDEX] |= (1<<30);							//Habilitar Reloj FTM3, se habilita CGC bit 30 (C29-603)
	FTM3 -> SC = (1<<19) + (1<<18) + (1<<16) + (1<<5) + (3<<3) + 3;	//Seleccionar fuente de reloj externa en CLKS bit 3-4 confg 11 ver diagrama (C27-550)
																	//Elegir el preescaner[8] del FTM3 bit 0-2 confg 011 (C45-1205)
																	//Modo up-down CPWM bit 5 confg "1" (C45-1205)
																	//Habilitar PWMENn del Ch0 y Ch1 bit 16-23 confg 3<<16 (C45-1205)

	FTM3 -> MOD = 250;     									//Establecer el periodo del PWM = 2000kHz (C45-1208)
	FTM3 -> CNTIN = 1;										//Establecer el valor inicial del timer (C45-1213)
	FTM3 -> CNT = 1;										//Reiniciar el timer con su valor inicial (C45-1207)

	FTM3 -> CONTROLS[0].CnSC = (1<<6)+(2<<2);         		//Elegir center PWM del Ch[0] bit 2-5 confg "1" (C45-1209), ver diagrama (C45-1268)
	FTM3 -> CONTROLS[2].CnSC = (1<<6)+(2<<2);         		//Elegir center PWM del Ch[1] bit 2-5 confg "1" (C45-1209), ver diagrama (C45-1268)
	FTM3 -> CONTROLS[3].CnSC = (1<<6)+(2<<2);         		//Elegir center PWM del Ch[3] bit 2-5 confg "1" (C45-1209), ver diagrama (C45-1268)

	FTM3 -> CONTROLS[0].CnV = 0;  							//Motor 1_A apagado (C45-1212)
	FTM3 -> CONTROLS[2].CnV = 0;  							//Motor 1_B apagado (C45-1212)
	FTM3 -> CONTROLS[3].CnV = 0;
}

void PWM(unsigned int duty_cycle_1, unsigned int duty_cycle_2, unsigned int duty_cycle_3){
	//Derecha, Izquierda, Actuador
	FTM3 -> CONTROLS[0].CnSC = (1<<6)+(2<<2);         		//Elegir center PWM del Ch[0] bit 2-5 confg "1" (C45-1209), ver diagrama (C45-1268)
	FTM3 -> CONTROLS[2].CnSC = (1<<6)+(2<<2);         		//Elegir center PWM del Ch[1] bit 2-5 confg "1" (C45-1209), ver diagrama (C45-1268)
	FTM3 -> CONTROLS[3].CnSC = (1<<6)+(2<<2);         		//Elegir center PWM del Ch[1] bit 2-5 confg "1" (C45-1209), ver diagrama (C45-1268)

	FTM3 -> CONTROLS[0].CnV = (duty_cycle_1*250/100);  		//Motor 1_A apagado (C45-1212)
	FTM3 -> CONTROLS[2].CnV = (duty_cycle_2*250/100);  		//Motor 1_B apagado (C45-1212)
	FTM3 -> CONTROLS[3].CnV = (duty_cycle_3*250/100);  		//Motor 1_B apagado (C45-1212)
}

