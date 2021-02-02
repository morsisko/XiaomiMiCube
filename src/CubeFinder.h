#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

class CubeFinder
{
private:
	BLEAdvertisedDevice cube;
	bool found = false;
public:
	static bool isCube(BLEAdvertisedDevice device);
	
	CubeFinder();
	void scan(int duration, bool active = true, int interval = 100, int window = 99);
	bool isCubeFound();
	BLEAdvertisedDevice getCubeDevice();
	void clear();
	~CubeFinder();
};