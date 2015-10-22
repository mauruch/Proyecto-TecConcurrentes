#include <vector>
#include <unistd.h>

using namespace std;

namespace utils {

typedef struct sharedDataConfig {

	unsigned int shipConfig;
	unsigned int truckConfig;
	unsigned int craneConfig;
	unsigned int dockConfig;

} sharedDataConfig;

/**
 * Structure that contains information of all Ships
 * available on any time.
 */
struct availableShip {
	bool available;
	std::string shipFifo;
};

/**
 * Structure that contains information of all trucks
 * available on any time.
 */
struct availableTruck {
	bool available;
	std::string  truckFifo;
};

/**
 * Structure that contains information of all cranes
 * available on any time.
 */
struct availableCrane {
	bool available;
	std::string  craneFifo;
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
