/*
 * Delay.cpp
 *
 *  Created on: 2014�~8��3��
 *      Author: YunKei
 */

#include <Delay.h>

void Delay::Simple100Delay(){

	__asm__ __volatile__("MOV	R0,#40\n\t"
						"1:"
						"SUB	R0,#1\n\t"
						"CMP	R0,#0\n\t"
						"BNE	1b");
}

void Delay::DelayUS(uint16_t nus){

	for(uint16_t i = 0; i < nus; i++){
		Simple100Delay();
	}
}

void Delay::DelayMS(uint16_t nms){

	for(uint16_t i = 0; i < nms; i++){
		DelayUS(1000);
	}
}

