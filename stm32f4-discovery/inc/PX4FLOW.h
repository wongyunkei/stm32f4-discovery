/*
 * PX4FLOW.h
 *
 *  Created on: 2015�~5��13��
 *      Author: YunKei
 */

#ifndef PX4FLOW_H_
#define PX4FLOW_H_

#include <math.h>
#include <Kalman.h>
#include <Quaternion.h>
#include <I2C.h>
#include <Eigen/Eigen>
using Eigen::Vector3f;

namespace Sensors{
	class PX4FLOW{
		public:
			PX4FLOW(I2C_TypeDef* I2Cx, float interval);
			static PX4FLOW* getInstance();
			void Update();
			Vector3f getTranslation();
			void reset();
		private:
			Vector3f Translation;
			I2C_TypeDef* PX4FLOW_I2C;
			float Interval;
			float prevZ;
			Kalman* flowKalman[3];
			float offset[3];
//			UKF* flowUKF;

	};
};

using namespace Sensors;

#endif /* PX4FLOW_H_ */
