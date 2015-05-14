/*
 * PX4FLOW.cpp
 *
 *  Created on: 2015¦~5¤ë13¤é
 *      Author: YunKei
 */

#include <PX4FLOW.h>

PX4FLOW* _mPX4FLOW;

PX4FLOW::PX4FLOW(I2C_TypeDef* I2Cx, double interval) : PX4FLOW_I2C(I2Cx), Interval(interval), prevZ(0){
	_mPX4FLOW = this;
	Translation.setZero();
}

PX4FLOW* PX4FLOW::getInstance(){
	return _mPX4FLOW;
}

void PX4FLOW::Update(){
	uint8_t data[22];
	int16_t temp;

	if(!I2C::getInstance(PX4FLOW_I2C)->BurstRead(0x42, 0x00, 22, data)){
		return;
	}

	double velocityX = 0;
	double velocityY = 0;
	double posZ = 0;
	double cosRcosP = cosf(Quaternion::getInstance()->getEuler(0)) * cosf(Quaternion::getInstance()->getEuler(1));
	temp = (int16_t)((uint16_t)data[6] | ((uint16_t)data[7] << 8));
	velocityX = ((double)temp) / 1000.0;
	velocityX *= cosRcosP;
	temp = ((uint16_t)data[8] | ((uint16_t)data[9] << 8));
	velocityY = ((double)temp) / 1000.0;
	velocityY *= cosRcosP;
	temp = ((uint16_t)data[20] | ((uint16_t)data[21] << 8));
	posZ = ((double)temp) / 1000.0;
	Translation(0) = velocityX * Interval;
	Translation(1) = velocityY * Interval;
	Translation(2) = (posZ - prevZ);
	prevZ = posZ;
}

Vector3d PX4FLOW::getTranslation(){
	return Translation;
}


