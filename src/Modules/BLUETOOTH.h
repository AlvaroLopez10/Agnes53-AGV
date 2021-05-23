/*
 * BLUETOOTH.h
 *
 *  Created on: 15/11/2019
 *      Author: alvar
 */

#ifndef MODULES_BLUETOOTH_H_
#define MODULES_BLUETOOTH_H_

void sensorCurrent(int number);
void sensorVoltage(int number);
void sensorRev1(int number);
void sensorRev2(int number);
void sensorVelocity(int number);
void sensorOrientation(int number);
void sendBluetooth (void);

#endif /* MODULES_BLUETOOTH_H_ */
