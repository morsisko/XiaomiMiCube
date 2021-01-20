#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>
#include <BLEAdvertisedDevice.h>

static BLEUUID realUUID("0000aadb-0000-1000-8000-00805f9b34fb");
static BLEUUID charUUID("0000aadc-0000-1000-8000-00805f9b34fb");
static BLEUUID serviceUUID("0000fe95-0000-1000-8000-00805f9b34fb");

class Cube
{
private:
	BLEClient* pClient;
	
public:
	Cube();
	void connect(BLEAdvertisedDevice device);
	
	
};