/*
 * Vector.cpp
 *
 *  Created on: 2014�~8��24��
 *      Author: YunKei
 */

#include <Vector.h>

void Vector::Add(float* v, float* v1, float* v2){
	for(int i = 0; i < 3; i++){
		v[i] = v1[i] + v2[i];
	}
}

void Vector::Scale(float* v, float* v1, float scale){
	for(int i = 0; i < 3; i++){
		v[i] = v1[i] * scale;
	}
}

void Vector::Multiplication(float* vout, float m[3][3], float* v){

	float temp[3];
	for(int i = 0; i < 3; i++){
		temp[i] = m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2];
	}

	for(int i = 0; i < 3; i++){
		vout[i] = temp[i];
	}
}

float Vector::DotProduct(float* v1, float* v2){
	float v = 0;
	for(int i = 0; i < 3; i++){
		v += v1[i] * v2[i];
	}
	return v;
}

void Vector::CrossProduct(float* v, float* v1, float* v2){
	float temp[3];
	temp[0] = v1[1] * v2[2] - v1[2] * v2[1];
	temp[1] = v1[2] * v2[0] - v1[0] * v2[2];
	temp[2] = v1[0] * v2[1] - v1[1] * v2[0];
	v[0] = temp[0];
	v[1] = temp[1];
	v[2] = temp[2];
}
