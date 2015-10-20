#include <vector>
#include <unistd.h>

using namespace std;

namespace utils {

struct sharedDataConfig {

	unsigned int craneConfig;
	unsigned int shipConfig;
	unsigned int truckConfig;
	unsigned int placesPortConfig;

};

struct sharedDockPort {

	sharedDockPort(int places){
		capacity = places;
		}

	vector<int> docksPort;
	int capacity;

};

}

