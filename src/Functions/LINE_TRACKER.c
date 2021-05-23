/*
 * LINE_TRACKER.c
 *
 *  Created on: 23/11/2019
 *      Author: alvar
 */

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "LINE_TRACKER.h"
#include "../Init_Settings/INIT_UART0.h"

extern unsigned char arr_rasp[3];
float CONTROL = 0.03164556962;
float pwm_front_left = 25;
float pwm_front_right = 20;
unsigned int pwm_right;
unsigned int pwm_left;
unsigned int side; //0 left, 1 right
int error;


void lineTracker(void) {

	side = arr_rasp[1];
	error = arr_rasp[2];

	if (error < 9) {
		pwm_right = 30;
		pwm_left = 35;
	} else if (error < 47) {
		if (side == 0) {
			pwm_left = 45;
			pwm_right = 33;
		} else {
			pwm_left = 40;
			pwm_right = 40;
		}
	} else {
		if (side == 0) {
			pwm_left = 55;
			pwm_right = 0;
		}else {
			pwm_left = 0;
			pwm_right = 50;
		}
	}

	pwm_right = 100 - pwm_right;
	pwm_left = 100 - pwm_left;

	/* if (arr_rasp[1]==0) {

		pwn_left = 100 - 35;
		pwm_right = 100 - 23;
		pwn_left = 100 - (pwm_front_left - CONTROL*error);
		pwm_right = 100 - (pwm_front_right + CONTROL*error);

	}else {

		pwn_left = 100 - 30;
		pwm_right = 100 - 30;
		pwn_left = 100 - (pwm_front_left + CONTROL*error);
		pwm_right = 100 - (pwm_front_right - CONTROL*error);

	} */
}
