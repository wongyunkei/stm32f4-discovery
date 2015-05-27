/*
 * UKF.h
 *
 *  Created on: 2015�~4��17��
 *      Author: YunKei
 */

#ifndef UKF_H_
#define UKF_H_

#include <stdio.h>
#include <Eigen/Eigen>
using Eigen::Matrix3f;
using Eigen::Matrix3d;
using Eigen::Vector3f;
using Eigen::Vector3d;

namespace Math
{
    class UKF
    {
    	public:
    		UKF(Vector3f x, Matrix3f p, Matrix3f q, Matrix3f r, float k = 50.0f, float a = 0.25f);
    		static UKF* getInstance();
    		void getSigmaPoints(Vector3f x[7]);
    		Vector3f Filtering(Vector3f x[7], Vector3f z[7], Vector3f Z);
    		static void printMat(char* ch, int index,  Matrix3f x);
    		static void printVect(char* ch, int index,  Vector3f x);
    	private:

    		void CalcSigmaPoints();
    		void CalcEstimation(Vector3f x[7], Vector3f z[7]);
    		void CalcMeasurement(Vector3f x[7], Vector3f z[7], Vector3f Z);
    		Vector3f predictX;
    		Vector3f correctX;
    		Matrix3f predictP;
    		Matrix3f correctP;
    		Vector3f predictZ;
    		Matrix3f Q;
    		Matrix3f R;
    		Vector3f S[7];
    		float Wm[7];
    		float Wc[7];
    		Matrix3f KalmanGain;
        	float K;
        	float lambda;
        	float _a;
    };
};

using namespace Math;

#endif /* UKF_H_ */
