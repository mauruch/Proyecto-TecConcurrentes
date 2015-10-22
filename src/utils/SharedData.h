#ifndef SHARED_DATA_H_
#define SHARED_DATA_H_

#include <vector>
#include <unistd.h>

using namespace std;

namespace utils {

struct sharedDataConfig {

	unsigned int shipConfig;
	unsigned int truckConfig;
	unsigned int craneConfig;
	unsigned int dockConfig;

} ;

struct readOnlysharedData {

	sharedDataConfig config;

	int idSemAvailableDocks;
	int idSemAvailableShips;
	int idSemAvailableTrucks;
	int idSemAvailableCranes;

	unsigned long m_collection = 0;

};

}

#endif /* DOMAIN_SHIP_H_ */
