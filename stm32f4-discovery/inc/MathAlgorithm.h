/*
 * MathAlgorithm.h
 *
 *  Created on: 2015�~4��17��
 *      Author: YunKei
 */

#ifndef MATHALGORITHM_H_
#define MATHALGORITHM_H_

#include <Eigen/Eigen>
using Eigen::Matrix3d;

namespace Math{

	class MathAlgorithm
    {
    	public:
			static void EigenDecomposition(Matrix3d A, Matrix3d& D, Matrix3d& V);

    	private:
    };
};

using namespace Math;

#endif /* MATHALGORITHM_H_ */
