/*
 * utils.h
 *
 *  Created on: Aug 16, 2023
 *      Author: steven
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <cstdlib>
using namespace std;

namespace model {

const long maxRand = 1000000L;

inline double randomDouble(double min, double max) {
	double randomValue = min + (max - min) * (random() % maxRand) / maxRand;
	return randomValue;
};

} /* namespace models */

#endif /* UTILS_UTILS_H_ */
