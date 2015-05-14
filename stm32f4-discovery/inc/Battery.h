/*
 * Battery.h
 *
 *  Created on: 2014�~11��30��
 *      Author: YunKei
 */

#ifndef BATTERY_H_
#define BATTERY_H_

#include <inttypes.h>

namespace Debug{
	class Battery{
		public:
			Battery();
			static Battery* getInstance();
			double getBatteryLevel();
		private:
			uint16_t BatteryLevelBuffer;
			double BatteryLevel;
	};
};

using namespace Debug;

#endif /* BATTERY_H_ */
