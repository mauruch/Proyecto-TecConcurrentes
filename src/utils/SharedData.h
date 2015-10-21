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

struct sharedData {

	sharedDataConfig config;
	vector<availableDock> availableDocks;
	vector<availableShip> availableShips;
	vector<availableTruck> availableTrucks;
	vector<availableCrane> availableCranes;
	int idSemAvailableDocks;
	int idSemAvailableShips;
	int idSemAvailableTrucks;
	int idSemAvailableCranes;

};
}
