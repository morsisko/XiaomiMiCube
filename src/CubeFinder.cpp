#include "CubeFinder.h"

bool CubeFinder::isCube(BLEAdvertisedDevice* device)
{
	if (!device->haveServiceData())
		return false;
	
	if (!device.getServiceDataUUID().equals(xiaomiUUID))
		return false;
	
	const std::string data = device->getServiceData();
	
	return data[2] == 0xE1 && data[3] == 0x4;
}

CubeFinder::CubeFinder()
{
	BLEDevice::init();
	scan = BLEDevice::getScan();
	cube = nullptr;
}

void CubeFinder::scan(int duration, bool active, int interval, int window)
{
	cube = nullptr;
	scan->setActiveScan(active); //active scan uses more power, but get results faster
	scan->setInterval(interval);
	scan->setWindow(window);  // less or equal setInterval value
	BLEScanResults foundDevices = scan->start(duration, false);
	
	for (int i = 0; i < foundDevices.getCount(); i++)
	{
		BLEAdvertisedDevice* foundDevice = foundDevices.getDevice(i);
		if (isCube(foundDevice))
		{
			cube = foundDevice;
			break;
		}
	}
}

BLEAdvertisedDevice* CubeFinder::getCubeDevice()
{
	return cube;
}

bool CubeFinder::isCubeFound()
{
	return cube != nullptr;
}

void CubeFinder::clear()
{
	scan->clearResults();
}

CubeFinder::~CubeFinder()
{
	clear();
}