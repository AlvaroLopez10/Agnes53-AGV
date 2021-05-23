/*
 * INIT_I2C.c
 *
 *  Created on: 20/11/2019
 *      Author: alvar
 */

#include "S32K144.h"  //include peripheral declarations S32K144
#include "math.h"
#include "../Modules/BLUETOOTH.h"

int8_t acx[2];
int8_t acy[2];
int8_t acz[2];

float acceleration_x;
float acceleration_y;
float acceleration_z;
unsigned char error = 0;
int write_bus = 0;

void SIRC_div(void)
{
    SCG->SIRCCSR &= ~ (1 << 24);   					//Slow IRC Control Status Register, apagar bit 24 para escribir en registro
    SCG->SIRCCSR &= ~ (1 << 0);   					//Disable Slow IRC
    SCG->SIRCCSR |= (1 << 0);						//Enable Slow IRC
    while((SCG->SIRCCSR & (1 << 24)) == 0); 		//wait until clock is valid, Slow IRC is enabled and output clock is valid
}

void initI2C(void){

	SIRC_div();
    PCC->PCCn[PCC_LPI2C0_INDEX] |= 2<<24;  			// SIRCDIV2_CLK (8 MHz) combinacion 010
    PCC->PCCn[PCC_LPI2C0_INDEX] |= 1<<30;			//habilitar clk LPI2C0

    LPI2C0->MCCR0 = 0x040409;						//[24] DATAVD 0x02, [16] SETHOLD 0x04, [8] CLKHI 0x05, [0] CLKLO 0x0B
    LPI2C0->MIER = (1<<10);							//NACK detect interrupt enable
    LPI2C0->MCR = 0x301; 							//Receive & Transmit FIFO reset, master logic enabled
}

static unsigned char bus_busy(void)				//I2C Bus is idle/busy
{
     error = 0;                					 // CLEAR ALL ERRORS
     unsigned int timeout_b = 0;
     while ((LPI2C0->MSR & (1 << 25)) && (timeout_b < 1000))  ++timeout_b; //Bus Busy flag

     if(timeout_b >= 1000) return (error |= (1 << 1));

     return 0;
}

void generate_start_ACK(uint8_t address)
{
    uint32_t command    = (address << 0);	//Transmit address in DATA[7:0]
    command             |= (0b100 << 8);
    LPI2C0->MTDR = command;					//Generate (repeated) START
}
static void transmit_data(uint8_t data)
{
    LPI2C0->MTDR = data;					//Transmit DATA[7:0]
}
static uint8_t generate_stop(void)
{
    uint32_t timeout_s      = 0;
    uint8_t stop_sent_err   = 0;

    LPI2C0->MTDR = 0x0200; 						//generate stop condition
    while((!(LPI2C0->MSR & (1 << 9))) && (!stop_sent_err)) //(1<<9): STOP detect flag
    {
        if(timeout_s > 3000)					//hold time para STOP
        {
            error |= (1 << 3);
            stop_sent_err = 1;
        }
        timeout_s++;
    }

    if(LPI2C0->MSR & (1 << 9))
    {
        LPI2C0->MSR |= (1 << 9); 				// Clear Stop flag
    }

     if(error) return error;
     else return 0;
}
static void receive_data(int8_t *p_buffer, uint8_t n_bytes)
{
    uint8_t  n;
    uint16_t time=0;
    uint16_t timeout_r = (2000 * n_bytes);
    uint16_t command;

    command =    0x0100;				//Receive (DATA[7:0] + 1) bytes
    command |=  (n_bytes - 1);
    LPI2C0->MTDR = command;

    while (((LPI2C0->MFSR) >> 16 != n_bytes) && (time < timeout_r)) ++time;

    if(time >= timeout_r)
    {
        LPI2C0->MCR |= (1 << 9);     // reset receive FIFO
        error |= (1 << 2);
    }
    else{
        for(n = 0; n < n_bytes; ++n)
        {
            p_buffer[n] = (uint8_t)(LPI2C0->MRDR & 0x000000FF);
        }
    }
}

uint8_t LPI2C0_write(uint8_t s_w_address, uint8_t s_reg_address, uint8_t byte)  //Write a single byte to a slave's register
{
    if(bus_busy()) return (error |= (1 << 1));
    generate_start_ACK(s_w_address);
    transmit_data(s_reg_address);
    transmit_data(byte);
    if(generate_stop()) return error;
    else return 0;
}

uint8_t LPI2C0_read(uint8_t s_r_address, uint8_t s_reg_address, int8_t *p_buffer, uint8_t n_bytes) // Read from a slave
{
    if(bus_busy()) return (error |= (1 << 1));
    generate_start_ACK(s_r_address - 1);
    transmit_data(s_reg_address);
    generate_start_ACK(s_r_address);
    receive_data(p_buffer, n_bytes);
    if(generate_stop()) return error;
    else return 0;
}

void readOrientation (void){
	//ACCELERATION_X

	if (write_bus == 0){
		LPI2C0_write((0x68<<1),0x6B,0x00);					//0X6b resetear Power management
		LPI2C0_write((0x68<<1),0x6C,0x00);					//0X6C Power management 2
		write_bus++;
	}

	LPI2C0_read((0x68<<1)+1,0x3B,acx,2);
	acceleration_x=((acx[0]<<8)+acx[1]);
	if(acceleration_x<0){
		acceleration_x=pow(acceleration_x,2);
		acceleration_x=sqrt(acceleration_x);
	}
	acceleration_x=((acceleration_x/16384)*1000);
	//ACCELERATION_Y
	LPI2C0_read((0x68<<1)+1,0x3D,acy,2);
	acceleration_y=((acy[0]<<8)+acy[1]);
	if(acceleration_y<0){
		acceleration_y=pow(acceleration_y,2);
		acceleration_y=sqrt(acceleration_y);
	}
	acceleration_y=((acceleration_y/16384)*1000);
	//ACCELERATION_Z
	LPI2C0_read((0x68<<1)+1,0x3F,acz,2);
	acceleration_z=((acz[0]<<8)+acz[1]);
	if(acceleration_z<0){
		acceleration_z=pow(acceleration_z,2);
		acceleration_z=sqrt(acceleration_z);
	}
	acceleration_z=((acceleration_z/16384)*1000);

	sensorOrientation(acceleration_x);
}
