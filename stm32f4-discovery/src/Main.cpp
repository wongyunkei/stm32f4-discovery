/*
 * Main.cpp
 *
 *  Created on: 2014¦~8¤ë2¤é
 *      Author: YunKei
 */

#include <inttypes.h>
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_usart.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Ticks.h>
#include <Task.h>
#include <Leds.h>
#include <Delay.h>
#include <Usart.h>
#include <Spi.h>
#include <I2C.h>
#include <MPU6050.h>
#include <Acceleration.h>
#include <Omega.h>
#include <Quaternion.h>
#include <MathTools.h>
#include <Vector.h>
#include <Communicating.h>
#include <Controlling.h>
#include <NRF905.h>
#include <stm32f4xx_dma.h>
#include <Battery.h>
#include <PWM.h>
#include <Sonic.h>
#include <PhasesMonitoring.h>
#include <Math.h>
#include <stm32f4xx_it.h>
#include <MathAlgorithm.h>
#include <Eigen/Eigen>
#include <UKF.h>
#include <PX4FLOW.h>
#include <SE3.h>

void TestMotorTask(){
	static double pwm;
	Usart::getInstance(USART1)->Print("%g,%g,%g,%g,%g\n", pwm,
			PhasesMonitoring::getInstance()->getRPM(0),
			PhasesMonitoring::getInstance()->getRPM(1),
			PhasesMonitoring::getInstance()->getRPM(2),
			PhasesMonitoring::getInstance()->getRPM(3));
	pwm += 100;
	if(pwm <= 6000){
		for(int i = 0; i < 4; i++){
			PWM::getInstant()->Control(i, pwm);
		}
	}else{
		for(int i = 0; i < 4; i++){
			PWM::getInstant()->Control(i, 0);
		}
	}
}

void InterruptPrint(){

	Usart::getInstance(USART1)->Print("T:%d\n", PhasesMonitoring::getInstance()->getInterruptCount());

	PhasesMonitoring::getInstance()->setInterruptCount(0);
}

int printfCount;

void RFOutput(){
	switch(Communicating::getInstant()->getPrintType()){
		case 0:
			Communicating::getInstant()->RFSend(0, (float)(MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(0))));
			Communicating::getInstant()->RFSend(1, (float)(MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(1))));
			Communicating::getInstant()->RFSend(2, (float)(MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(2))));
			break;
		case 1:
			Communicating::getInstant()->RFSend(0, (float)PhasesMonitoring::getInstance()->getRPM(0));
			Communicating::getInstant()->RFSend(1, (float)PhasesMonitoring::getInstance()->getRPM(1));
			Communicating::getInstant()->RFSend(2, (float)PhasesMonitoring::getInstance()->getRPM(2));
			Communicating::getInstant()->RFSend(3, (float)PhasesMonitoring::getInstance()->getRPM(3));
			break;
		case 2:
			Communicating::getInstant()->RFSend(0, (float)Acceleration::getInstance()->getAcc(0));
			Communicating::getInstant()->RFSend(1, (float)Acceleration::getInstance()->getAcc(1));
			Communicating::getInstant()->RFSend(2, (float)Acceleration::getInstance()->getAcc(2));
			break;
		case 3:
			Communicating::getInstant()->RFSend(0, (float)Acceleration::getInstance()->getMovingAverageFilter(0)->getAverage());
			Communicating::getInstant()->RFSend(1, (float)Acceleration::getInstance()->getMovingAverageFilter(1)->getAverage());
			Communicating::getInstant()->RFSend(2, (float)Acceleration::getInstance()->getMovingAverageFilter(2)->getAverage());
			break;
		case 4:
			Communicating::getInstant()->RFSend(0, (float)Omega::getInstance()->getOmega(0));
			Communicating::getInstant()->RFSend(1, (float)Omega::getInstance()->getOmega(1));
			Communicating::getInstant()->RFSend(2, (float)Omega::getInstance()->getOmega(2));
			break;
		case 5:
			Communicating::getInstant()->RFSend(0, (float)Acceleration::getInstance()->getFilteredAngle(0));
			Communicating::getInstant()->RFSend(1, (float)Acceleration::getInstance()->getFilteredAngle(1));
			break;
		case 6:
			Communicating::getInstant()->RFSend(0, (float)((SE3::getInstance()->getPos())(0)*100.0));
			Communicating::getInstant()->RFSend(1, (float)((SE3::getInstance()->getPos())(1)*100.0));
			Communicating::getInstant()->RFSend(2, (float)((SE3::getInstance()->getPos())(2)*100.0));
			break;
		case 7:
			Communicating::getInstant()->RFSend(0, (float)(PX4FLOW::getInstance()->getTranslation())(0)*100.0);
			Communicating::getInstant()->RFSend(1, (float)(PX4FLOW::getInstance()->getTranslation())(1)*100.0);
			Communicating::getInstant()->RFSend(2, (float)(PX4FLOW::getInstance()->getTranslation())(2)*100.0);
			break;

		case 8:
			break;
	}
}

void BatteryPrint(){
	Communicating::getInstant()->RFSend(4, (float)Battery::getInstance()->getBatteryLevel());
}

void Output(){

	UKF::printVect("pos", 0, SE3::getInstance()->getPos());
//	Usart::getInstance(USART1)->Print("$,%g,%g,%g,%g,%g\n", MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(0)),
//			MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(1)),
//			MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(2)),
//			MathTools::RadianToDegree(Acceleration::getInstance()->getAngle(0)),
//			MathTools::RadianToDegree(Acceleration::getInstance()->getAngle(1)));


//	Usart::getInstance(USART1)->Print("$,%g,%g\n", MathTools::RadianToDegree(Acceleration::getInstance()->getAngle(0)),
//			MathTools::RadianToDegree(Acceleration::getInstance()->getAngle(1)));


//	switch(Communicating::getInstant()->getPrintType()){
//		case 0:
//			Usart::getInstance(USART1)->Print("$,%g,%g,%g\n", MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(0)),
//					MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(1)),
//					MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(2)));
//			break;
//		case 1:
//			Usart::getInstance(USART1)->Print("$,%g,%g,%g,%g\n", PhasesMonitoring::getInstance()->getRPM(0),
//					PhasesMonitoring::getInstance()->getRPM(1),
//					PhasesMonitoring::getInstance()->getRPM(2),
//					PhasesMonitoring::getInstance()->getRPM(3));
//			break;
//		case 2:
//			Usart::getInstance(USART1)->Print("$,%g,%g,%g\n", Acceleration::getInstance()->getAcc(0),
//					Acceleration::getInstance()->getAcc(1),
//					Acceleration::getInstance()->getAcc(2));
//			break;
//		case 3:
//			Usart::getInstance(USART1)->Print("$,%g,%g,%g\n", Acceleration::getInstance()->getAcc(0),
//					Acceleration::getInstance()->getMovingAverageFilter(1)->getAverage(),
//					Acceleration::getInstance()->getMovingAverageFilter(2)->getAverage());
//			break;
//		case 4:
//				Usart::getInstance(USART1)->Print("$,%g,%g,%g\n", Omega::getInstance()->getOmega(0),
//				Omega::getInstance()->getOmega(1),
//				Omega::getInstance()->getOmega(2));
//			break;
//	}


//	printf("$,%g,%g,%g,", MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(0)),
//			MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(1)),
//			MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(2)));
//
//	printf("%g,%g,%g,", Omega::getInstance()->getOmega(0),
//				Omega::getInstance()->getOmega(1),
//			Omega::getInstance()->getOmega(2));
//
//	printf("%g,%g,%g\n", Acceleration::getInstance()->getAcc(0),
//				Acceleration::getInstance()->getAcc(1),
//				Acceleration::getInstance()->getAcc(2));
}

void Print(){

	float E[4];

	switch(Communicating::getInstant()->getPrintType()){
		case 0:
			for(int i = 0; i < 3; i++){
				E[i] = MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(i)) + Controlling::getInstant()->getRPYOffset(i);
			}
			E[3] = Communicating::getInstant()->getCmdData();
			break;
		case 1:
			for(int i = 0; i < 3; i++){
				E[i] = Acceleration::getInstance()->getAcc(i);
			}
			E[3] = Communicating::getInstant()->getCmdData();
			break;
		case 2:
			for(int i = 0; i < 3; i++){
				E[i] = Omega::getInstance()->getOmega(i);
			}
			E[3] = Communicating::getInstant()->getCmdData();
			break;
		case 4:
			for(int i = 0; i < 4; i++){
				E[i] = Controlling::getInstant()->getRotorPWM(i);
			}
			break;
		case 5:
			for(int i = 0; i < 3; i++){
				E[i] = Controlling::getInstant()->getRPYOffset(i);
			}
			E[3] = Communicating::getInstant()->getCmdData();
			break;
		case 6:
			for(int i = 0; i < 3; i++){
				E[i] = Sonic::getInstance()->getDistance();
			}
			E[3] = Communicating::getInstant()->getCmdData();
			break;
	}
//	Communicating::getInstant()->RFSend(0, E);
}

int t[2];

void Update(){
	MPU6050::getInstance()->Update();
	Omega::getInstance()->Update();
	Acceleration::getInstance()->Update();
	Quaternion::getInstance()->Update();
}

void UpdatePX4FLOW(){
	PX4FLOW::getInstance()->Update();
	SE3::getInstance()->Update();
}

void initUpdate(){
	MPU6050::getInstance()->Update();
	Omega::getInstance()->Update();
	Acceleration::getInstance()->Update();
}

void ReceiveTask(){
	Communicating::getInstant()->ReceivePoll();
}

void SendTask(){
	Communicating::getInstant()->SendPoll();
}

void ControlTask(){
	Controlling::getInstant()->ControllingPoll();
}

unsigned char Buffer[2048];
unsigned char rfBuffer[2048];
int BufferCount;
int Timeout;
int rfBufferCount;
int rfTimeout;


void RFTask(){
	int uartLength = Usart::getInstance(USART1)->getBufferCount();
	if(uartLength > 0){
		Usart::getInstance(USART1)->Read(Buffer + BufferCount, uartLength);
	}
	BufferCount += uartLength;
	if(BufferCount >= 8){
		unsigned char B[9];
		for(int i = 0; i < 8; i++){
			B[i] = Buffer[i];
		}
		B[8] = '\0';
		if(NRF905::getInstance()->Write("%s", B)){
			BufferCount -= 8;
			for(int i = 0; i < BufferCount; i++){
				Buffer[i] = Buffer[i + 8];
			}
		}
	}
}

void UartTask(){
	int rfLength = NRF905::getInstance()->getBufferCount();
	if(rfLength > 0){
		NRF905::getInstance()->Read(rfBuffer + rfBufferCount, rfLength);
	}
	rfBufferCount += rfLength;

	if(rfBufferCount >= 8){
		unsigned char B[9];
		for(int i = 0; i < 8; i++){
			B[i] = rfBuffer[i];
		}
		B[8] = '\0';
		rfBufferCount -= 8;
		for(int i = 0; i < rfBufferCount; i++){
			rfBuffer[i] = rfBuffer[i + 8];
		}
//		Usart::getInstance(USART1)->Print("%s", B);
		printf("%s", B);

	}
}

int rfResetCount;
int usartResetCount;

void rfReset(){
	if(rfResetCount++ > 10){
		rfResetCount = 0;
		Leds::getInstance()->Toggle(Leds::LED2);
		NRF905::getInstance()->resetNRF905();
		rfBufferCount = 0;
		Usart::getInstance(USART1)->Print("RF RESETED\n");
	}
}

void usartReset(){
	if(usartResetCount++ > 10){
		usartResetCount = 0;
		Leds::getInstance()->Toggle(Leds::LED2);
		//Usart::getInstance(USART3)->reset();
		BufferCount = 0;
		Usart::getInstance(USART1)->Print("USART RESETED\n");
	}
}

void Test(){
	//Usart::getInstance(USART1)->Print("Plot:%g,%g,%g\n", Quaternion::getInstance()->getEuler(0), Quaternion::getInstance()->getEuler(1), Quaternion::getInstance()->getEuler(2));
	//Usart::getInstance(USART1)->Print("BatteryLevel:%g\n", Battery::getInstance()->getBatteryLevel());
	//Usart::getInstance(USART1)->Print("%d\n", Ticks::getInstance()->getTicks());
	Usart::getInstance(USART1)->Print("Plot:%g,%g,%g,%g\n", Controlling::getInstant()->getFzPWM() * 3600 / _K / CT);//,
//			Controlling::getInstant()->getRotorPWM(1),
//			Controlling::getInstant()->getRotorPWM(2),
//			Controlling::getInstant()->getRotorPWM(3));
}

int main1(){

	Delay::DelayMS(100);
	Task mTask;
	Leds mLeds;

	Usart mUsart1(USART1, 256000);
	uint8_t rxAddress[4] = {0x01, 0x09, 0x08, 0x07};
	uint8_t txAddress[4] = {0x01, 0x00, 0x00, 0x08};
	NRF905 mNRF905(8, NRF905::FREQ_433M, NRF905::PWR_POS_10dBM, NRF905::RX_NORMAL_PWR, NRF905::NO_RETRAN, rxAddress, txAddress, 8, 8);

	BufferCount = 0;
	rfBufferCount = 0;
	mLeds.Blink(100, Leds::LED1, true);
	mTask.Attach(20, 0, UartTask, true, -1);
	mTask.Attach(20, 0, RFTask, true, -1);
	mTask.Run();
}

void SonicUpdateTask(){
	Sonic::getInstance()->Update();
}


void Sampling(){
}

float sonarValue;

void TIM4_IRQHandler(){
	if(TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET){
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13)){
			TIM_SetCounter(TIM4, 0);
		}
		else{
			float f = (float)TIM_GetCapture2(TIM4);
			sonarValue = f * 0.7619f / 58.0f;
			Usart::getInstance(USART3)->Print("%g\n", sonarValue);
		}
		TIM_ClearITPendingBit(TIM4, TIM_IT_CC2);
	}
}

void SonarConfig(){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);

	TIM_TimeBaseStructure.TIM_Prescaler = 64-1;
	TIM_TimeBaseStructure.TIM_Period = 0xffff;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0xf;

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_Init(&NVIC_InitStructure) ;

	TIM_Cmd(TIM4, ENABLE);
	TIM_ITConfig(TIM4, TIM_IT_CC2, ENABLE);
	sonarValue = 0;
}

void ReadSonar(){
	Leds::getInstance()->Toggle(Leds::LED3);
	Usart::getInstance(USART3)->Print("%g\n", sonarValue);
}

void Testing(){
//	Usart::getInstance(USART3)->Print("$,%g,%g,%g\n", MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(0)),
//														MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(1)),
//														MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(2)));
////	printf("t:%d\n", t[1] - t[0]);
//	Communicating::getInstant()->RFSend(0, (float)Omega::getInstance()->getOmega(0));
//	Communicating::getInstant()->RFSend(1, (float)Omega::getInstance()->getOmega(1));
//	Communicating::getInstant()->RFSend(2, (float)Omega::getInstance()->getOmega(2));

//	Communicating::getInstant()->RFSend(0, (float)(MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(0))));
//	Communicating::getInstant()->RFSend(1, (float)(MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(1))));
//	Communicating::getInstant()->RFSend(2, (float)(MathTools::RadianToDegree(Quaternion::getInstance()->getEuler(2))));

}
extern uint32_t heap_loc;
void MTest(){

}

void printTaskDuration(){
	for(int i = 0; i < Task::getInstance()->TasksNum; i++){
		Task::getInstance()->printDeration(i);
	}
}

int main(){

	Delay::DelayMS(100);
	Task mTask;
	Leds mLeds;
	Battery mBattery;
	Usart mUsart3(USART3, 115200);
	Usart::setPrintUsart(USART3);
	mLeds.LedsControl(mLeds.LED3, true);
	Communicating mCommunicating(USART3, false);
	Controlling mControlling;
	I2C* mI2C1 = new I2C(I2C1, I2C::SPEED_400K);
	I2C* mI2C2 = new I2C(I2C2, I2C::SPEED_400K);
	MPU6050 mMPU6050(0.002);
	Acceleration mAcceleration;
	Omega mOmega;
	Quaternion mQuaternion(0.002);
	PX4FLOW(I2C1, 0.006);
	SE3* mSE3 = new SE3();

	Delay::DelayMS(100);
	mLeds.LedsControl(Leds::LED4, true);
	mLeds.Blink(100, Leds::LED1, true);
	mTask.Attach(2, 0, initUpdate, false, 128);
	mTask.Run();
//
	mTask.Attach(2, 0, Update, true, -1);
	mTask.Attach(6, 1, UpdatePX4FLOW, true, -1);
	mTask.Attach(40, 3, ReceiveTask, true, -1);
	mTask.Attach(40, 17, SendTask, true, -1);
	mTask.Attach(200, 61, RFOutput, true, -1);
//	mTask.Attach(100, 41, Output, true, -1);
//	mTask.Attach(100, 61, printTaskDuration, true, -1);
//	mTask.Attach(100, 0, Testing, true, -1);
//	mTask.Attach(500, 0, MTest, true, -1);
//	mLeds.Blink(100, Leds::LED1, true);
	mTask.Run();
//	while(true){
//		IWDG_ReloadCounter();
//		GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
//		Delay::DelayMS(1000);
//	}

//	Controlling mControlling;
//	SonarConfig();

//	uint8_t txAddress[4] = {0x01, 0x09, 0x08, 0x07};
//	uint8_t rxAddress[4] = {0x01, 0x00, 0x00, 0x08};
//	NRF905 mNRF905(8, NRF905::FREQ_433M, NRF905::PWR_POS_10dBM, NRF905::RX_NORMAL_PWR, NRF905::NO_RETRAN, rxAddress, txAddress, 8, 8);
//	Communicating mCommunicating(USART1, true);

//	PhasesMonitoring mPhasesMonitoring;
//

//	Sonic mSonic;

//	Usart::getInstance(USART1)->Print("V:%g\n", Battery::getInstance()->getBatteryLevel());
//	printfCount = 0;
//	mTask.Attach(2, 0, Update, true, -1);
////	mTask.Attach(60, 0, SonicUpdateTask, true, -1);
//	mTask.Attach(2, 0, ControlTask, true, -1);
//	mTask.Attach(20, 0, ReceiveTask, true, -1);
//	mTask.Attach(20, 10, SendTask, true, -1);
////	mTask.Attach(100, 50, Output, true, -1);
//	mTask.Attach(100, 50, RFOutput, true, -1);
////	mTask.Attach(100, 50, Sampling, true, -1);
//	mTask.Attach(5000, 120, BatteryPrint, true, -1);
////	mTask.Attach(1000, 0, InterruptPrint, true, -1);
//	mTask.Attach(100, 0, Testing, true, -1);
	//mTask.Attach(100, 50, ReadSonar, true, -1);
//	mTask.Attach(100, 50, Sampling, true, -1);

	return 0;
}

void HardFault_Handler(){
//	printf("HardFault:\nHeap:%lx\n\n", heap_loc);
}
