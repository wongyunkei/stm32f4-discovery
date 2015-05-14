/*
 * Quaternion.h
 *
 *  Created on: 2014�~8��24��
 *      Author: YunKei
 */

#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <Kalman.h>
#include <UKF.h>
#include <Pid.h>

namespace Math{

	class Quaternion{

		public:
			Quaternion(double);
			static Quaternion* getInstance();
			void Update();
			double getEuler(int);
			void setEuler(int, double);
			double* getQuaternion();
			void getQuaternionConjugate(double*,double*);
			void resetQuaternion();
			Matrix3d getRotationMatrix();
			double getInitAngles(int index);
			Kalman* getKalman(int index);
			Vector3d temp;

		private:

			double Interval;
			double _Quaternion[4];
			Kalman* _EulerKalman[3];
			UKF* _EulerUKF;
			double _Euler[3];
			double InitAngles[2];
			double PreAcc[3];
			Pid* DriftCorrectionPid[3];
			void Normalization(double*, double*);
			void QuaternionMultiplication(double*, double*,  double*);
			void EulerToQuaternion(double*, double*);
			void QuaternionToEuler(double*, double*);
			Matrix3d QuaternionToMatrix(double* quaternion);
	};
};

using namespace Math;

#endif /* QUATERNION_H_ */
