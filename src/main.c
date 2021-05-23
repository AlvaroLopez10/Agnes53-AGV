/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "./Init_Settings/INIT.h"
#include "./Init_Settings/INIT_PORTE.h"
#include "./Init_Settings/INIT_UART2.h"
#include "./Init_Settings/INIT_UART0.h"
#include "./Init_Settings/INIT_FTM.h"
#include "./Init_Settings/INIT_FTM0.h"
#include "./Init_Settings/INIT_LPIT0.h"
#include "./Init_Settings/INIT_ADC0.h"
#include "./Init_Settings/INIT_I2C.h"
#include "./Functions/MANUAL.h"

int main(void)
{

	init();
	initPortE();
	initUART2();
	initUART0();
	initFTM3();
	initFTM0();
	initADC0();
	initI2C();
	initLPIT0();

    for(;;) {
    }

	return 0;
}
