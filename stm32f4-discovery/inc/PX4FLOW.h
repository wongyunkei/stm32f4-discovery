/*
 * PX4FLOW.h
 *
 *  Created on: 2015¦~5¤ë13¤é
 *      Author: YunKei
 */

#ifndef PX4FLOW_H_
#define PX4FLOW_H_

#include <math.h>
#include <Quaternion.h>
#include <I2C.h>
#include <Eigen/Eigen>
using Eigen::Vector3d;

namespace Sensors{
	class PX4FLOW{
		public:
			PX4FLOW(I2C_TypeDef* I2Cx, double interval);
			static PX4FLOW* getInstance();
			void Update();
			Vector3d getTranslation();
		private:
			Vector3d Translation;
			I2C_TypeDef* PX4FLOW_I2C;
			double Interval;
			double prevZ;

	};
};

using namespace Sensors;

#endif /* PX4FLOW_H_ */
