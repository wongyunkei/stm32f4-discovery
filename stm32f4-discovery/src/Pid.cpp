/*
 * Pid.cpp
 *
 *  Created on: 2014�~11��8��
 *      Author: YunKei
 */

#include <Pid.h>
#include <stdio.h>
#include <Ticks.h>
#include <MathTools.h>

Pid* _mPid[20];

Pid::Pid(int index, double kp, double ki, double kd, double integralLimit, double t) : Kp(kp), Ki(ki), Kd(kd), Integral(0), IntegralLimit(integralLimit), PreErr(0), DefaultPeriod(t), Period(t), PreTimeStamp(0){
	_mPid[index] = this;
}

Pid* Pid::getInstance(int index){
	return _mPid[index];
}

double Pid::setPid(double kp, double ki, double kd){
	Kp = kp;
	Ki = ki;
	Kd = kd;
}

double Pid::getPid(int index){
	double v = 0;

	switch(index){
		case 0:
			v = Kp;
			break;
		case 1:
			v = Ki;
			break;
		case 2:
			v = Kd;
			break;

	}

	return v;
}

void Pid::clear(){
	Integral = 0;
	PreErr = 0;
	PreTimeStamp = 0;
}

double Pid::pid(double target, double current){
	double t = Ticks::getInstance()->getTicks();
	t /= 1000;
	if(PreTimeStamp > 0){
		Period = t < PreTimeStamp ? (10000 - PreTimeStamp + t) : t - PreTimeStamp;
	}
	else{
		Period = DefaultPeriod;
	}
	PreTimeStamp = t;
	double err = target - current;
	Integral += err;
	Integral = MathTools::Trim(Integral, -IntegralLimit, IntegralLimit);
	double derivative = err - PreErr;
	return Kp * err + Ki * Integral * Period + Kd * derivative / Period;
}
