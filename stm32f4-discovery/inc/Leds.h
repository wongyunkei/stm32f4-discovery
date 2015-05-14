/*
 * Leds.h
 *
 *  Created on: 2014�~8��3��
 *      Author: YunKei
 */

#ifndef LEDS_H_
#define LEDS_H_

#include <inttypes.h>

namespace Debug{

	class Leds{

		public:

			Leds();
			static Leds* getInstance();
			enum LEDS {LED1, LED2, LED3, LED4};
			void LedsControl(LEDS, bool);
			void Toggle(LEDS);
			void Blink(uint16_t, LEDS, bool);

		private:



	};
};

using namespace Debug;

#endif /* LEDS_H_ */
