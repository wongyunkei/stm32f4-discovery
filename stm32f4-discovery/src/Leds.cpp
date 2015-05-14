/*
 * Leds.cpp
 *
 *  Created on: 2014¦~8¤ë3¤é
 *      Author: YunKei
 */

#include <Leds.h>
#include <Task.h>
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

Leds* _mLeds;

Leds::Leds(){

	GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	_mLeds = this;
}

Leds* Leds::getInstance(){
	return _mLeds;
}

void Leds::LedsControl(LEDS leds , bool onState){

	switch(leds){

		case LED1:
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, onState ? Bit_SET : Bit_RESET);
			break;

		case LED2:
			GPIO_WriteBit(GPIOD, GPIO_Pin_13, onState ? Bit_SET : Bit_RESET);
			break;

		case LED3:
			GPIO_WriteBit(GPIOD, GPIO_Pin_14, onState ? Bit_SET : Bit_RESET);
			break;

		case LED4:
			GPIO_WriteBit(GPIOD, GPIO_Pin_15, onState ? Bit_SET : Bit_RESET);
			break;

		default:
			break;
	}
}

void Blink_Led1(){
	GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
}

void Blink_Led2(){
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
}

void Blink_Led3(){
	GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
}

void Blink_Led4(){
	GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
}

void Leds::Toggle(LEDS leds){
	if(leds == LED1){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	}
	else if(leds == LED2){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
	}
	else if(leds == LED3){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
	}
	else if(leds == LED4){
		GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
	}
}

void Leds::Blink(uint16_t period, LEDS leds, bool onState){

	switch(leds){

		case LED1:
			if(onState){

				Task::getInstance()->Attach(period, 0, Blink_Led1, true, -1);
			}
			else{

				Task::getInstance()->DeAttach(Blink_Led1);
			}
			break;

		case LED2:
			if(onState){

				Task::getInstance()->Attach(period, 0, Blink_Led2, true, -1);
			}
			else{

				Task::getInstance()->DeAttach(Blink_Led2);
			}
			break;

		case LED3:
			if(onState){

				Task::getInstance()->Attach(period, 0, Blink_Led3, true, -1);
			}
			else{

				Task::getInstance()->DeAttach(Blink_Led3);
			}
			break;

		case LED4:
			if(onState){

				Task::getInstance()->Attach(period, 0, Blink_Led4, true, -1);
			}
			else{

				Task::getInstance()->DeAttach(Blink_Led4);
			}
			break;
		default:
			break;
	}
}
