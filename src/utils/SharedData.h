#include <vector>
#include <unistd.h>

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

