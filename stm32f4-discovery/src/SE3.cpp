/*
 * SE3.cpp
 *
 *  Created on: 2015¦~5¤ë14¤é
 *      Author: YunKei
 */

#include <SE3.h>

SE3* _mSE3;

void SE3::printMat(char* ch, int index,  Matrix4d x){
	printf("\n%s:%d\n", ch, index);
	printf("%g  %g  %g  %g\n", x(0,0), x(0,1), x(0,2), x(0,3));
	printf("%g  %g  %g  %g\n", x(1,0), x(1,1), x(1,2), x(1,3));
	printf("%g  %g  %g  %g\n", x(2,0), x(2,1), x(2,2), x(2,3));
	printf("%g  %g  %g  %g\n", x(3,0), x(3,1), x(3,2), x(3,3));

}

void SE3::printVect(char* ch, int index,  Vector4d x){
	printf("\n%s:%d\n", ch, index);
	printf("%g  %g  %g  %g\n", x(0), x(1), x(2), x(3));

}

SE3::SE3(){
	_mSE3 = this;
	_SE3.setIdentity();
	_pos.setZero();
	_pos(3) = 1;
	pos.setZero();
	Vector3d x;
	Matrix3d p;
	Matrix3d q;
	Matrix3d r;
	x.setZero();
	p.setIdentity();
	q.setIdentity();
	r.setIdentity();
	q*=0.0001;
	r*=0.1;
	SE3UKF = new UKF(x, p, q, r);
}

SE3* SE3::getInstance(){
	return _mSE3;
}

void SE3::Update(){
	Vector3d x[7];
	Vector3d z[7];
	Vector4d temp;
	SE3UKF->getSigmaPoints(x);
	for(int i = 0; i < 7; i++){
//		UKF::getInstance()->printVect("x[i]", i, x[i]);
		for(int j = 0; j < 3; j++){
			temp(j) = x[i](j);
		}
		temp(3) = 1.0;
		temp = _SE3 * temp;
		for(int j = 0; j < 3; j++){
			z[i](j) = temp(j);
		}
//		UKF::getInstance()->printVect("z[i]", i, z[i]);
	}

	Matrix3d Rotation = Quaternion::getInstance()->getRotationMatrix();
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			_SE3(i,j) = Rotation(i,j);
		}
	}
	Vector3d Translation = PX4FLOW::getInstance()->getTranslation();
	for(int i = 0; i < 3; i++){
		_SE3(i,3) = Translation(i);
	}
	_pos = _SE3 * _pos;
	for(int i = 0; i < 3; i++){
		pos(i) = _pos(i);
	}
//	UKF::getInstance()->printVect("pos", 0, pos);
//	pos = SE3UKF->Filtering(x,z,pos);
//	UKF::getInstance()->printVect("pos", 1, pos);
}

Vector3d SE3::getPos(){
	return pos;
}

Matrix4d SE3::getSE3(){
	return _SE3;
}
