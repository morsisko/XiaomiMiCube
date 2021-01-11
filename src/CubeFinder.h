#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

class CubeFinder
{
private:
	BLEScan* scan;
	BLEAdvertisedDevice* cube;
public:
	static BLEUUID xiaomiUUID("0000fe95-0000-1000-8000-00805f9b34fb");
	static bool isCube(BLEAdvertisedDevice* device);
	
	CubeFinder();
	void scan(int duration, bool active = true, int interval = 100, int window = 99);
	bool isCubeFound();
	BLEAdvertisedDevice* getCubeDevice();
	void clear();
	~CubeFinder();
}