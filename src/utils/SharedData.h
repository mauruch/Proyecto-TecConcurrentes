/*
 * SharedData.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: mauruch
 */

#include <vector>
using namespace std;

namespace utils {
struct sharedData {

	unsigned int craneConfig;
	unsigned int shipConfig;
	unsigned int truckConfig;
	unsigned int placesPortConfig;

	vector<int> shipSemaphores;

};
}

