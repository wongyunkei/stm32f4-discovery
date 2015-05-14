/*
 * SE3.h
 *
 *  Created on: 2015¦~5¤ë14¤é
 *      Author: YunKei
 */

#ifndef SE3_H_
#define SE3_H_

#include <UKF.h>
#include <PX4FLOW.h>
#include <stdio.h>
#include <Quaternion.h>
#include <Eigen/Eigen>
using Eigen::Vector3d;
using Eigen::Vector4d;
using Eigen::Matrix4d;
using Eigen::Matrix3d;

namespace Math{
	class SE3{
		public:
			SE3();
			static SE3* getInstance();
			void Update();
			Vector3d getPos();
			void printMat(char* ch, int index,  Matrix4d x);
			void printVect(char* ch, int index, Vector4d x);
			Matrix4d getSE3();
		private:
			UKF* SE3UKF;
			Matrix4d _SE3;
			Vector4d _pos;
			Vector3d pos;
	};
};

using namespace Math;

#endif /* SE3_H_ */
