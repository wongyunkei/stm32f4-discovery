/*
 * Sonic.h
 *
 *  Created on: 2014�~12��18��
 *      Author: YunKei
 */

#ifndef SONIC_H_
#define SONIC_H_

#include <Kalman.h>

namespace Sensors{
	class Sonic{
		public:
			Sonic();
			static Sonic* getInstance();
			void Update();
			double getDistance();
			void setDistance(double);
			Kalman* getSonicKalman();
		private:
			double distance;
			Kalman* SonicKalman;
	};
};

using namespace Sensors;

#endif /* SONIC_H_ */
