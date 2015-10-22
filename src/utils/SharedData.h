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

/**
 * Structure that contains information of all Ships
 * available on any time.
 */
struct availableShip {
	bool available;
};

/**
 * Structure that contains information of all trucks
 * available on any time.
 */
struct availableTruck {
	bool available;
};

/**
 * Structure that contains information of all cranes
 * available on any time.
 */
struct availableCrane {
	bool available;
};

/**
 * Structure that contains information of all docks
 * available on any time.
 */
struct availableDock {
	bool available;
};

struct readOnlysharedData {

	sharedDataConfig config;

	int idSemAvailableDocks;
	int idSemAvailableShips;
	int idSemAvailableTrucks;
	int idSemAvailableCranes;

	int availableDockSharedDataId;
	int availableShipsSharedDataId;
	int availableCranesSharedDataId;
	int availableTrucksSharedDataId;

	unsigned long m_collection = 0;

};

struct availableDockSharedData {
	vector<availableDock> availableDocks;
};

struct availableShipsSharedData {
	vector<availableShip> availableShips;
};

struct availableCranesSharedData{
	vector<availableCrane> availableCranes;
};

struct availableTrucksSharedData{
	vector<availableTruck> availableTrucks;
};

}

#endif /* DOMAIN_SHIP_H_ */
