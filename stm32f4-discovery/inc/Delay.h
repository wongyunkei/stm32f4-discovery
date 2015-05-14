/*
 * Delay.h
 *
 *  Created on: 2014�~8��3��
 *      Author: YunKei
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <inttypes.h>

namespace Time{

	class Delay{

		public:

			static void DelayUS(uint16_t);
			static void DelayMS(uint16_t);

		private:

			static void Simple100Delay();
	};
};

using namespace Time;

#endif /* DELAY_H_ */
