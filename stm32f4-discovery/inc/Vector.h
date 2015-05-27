/*
 * Vector.h
 *
 *  Created on: 2014�~8��24��
 *      Author: YunKei
 */

#ifndef VECTOR_H_
#define VECTOR_H_

namespace Math{

	class Vector{

		public:
			static void Add(float*, float*, float*);
			static void Scale(float*, float*, float);
			static void Multiplication(float*, float[3][3], float*);
			static float DotProduct(float*, float*);
			static void CrossProduct(float*, float*, float*);
		private:
	};
};

using namespace Math;

#endif /* VECTOR_H_ */
