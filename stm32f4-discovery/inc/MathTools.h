/*
 * MathTools.h
 *
 *  Created on: 2014�~8��24��
 *      Author: YunKei
 */

#ifndef MATHTOOLS_H_
#define MATHTOOLS_H_

namespace Math{

	class MathTools{

		public:

			#define PI 3.14159f
			#define DEGREE_PER_RADIAN 57.2958f
			#define RADIAN_PER_DEGREE 0.01745f
			static float Sqrt(float);
			static float Sign(float);
			static float DegreeToRadian(float);
			static float RadianToDegree(float);
			static float Trim(float, float, float);
			static float CutOff(float, float, float);
			static float QuadRoot(float);
			static float OctRoot(float);
			static float TrimResolution(float value);

		private:


	};
};

using namespace Math;

#endif /* MATHTOOLS_H_ */
