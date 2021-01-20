#include "CubeFinder.h"

bool CubeFinder::isCube(BLEAdvertisedDevice device)
{
	if (!device.haveServiceData())
		return false;
	
	if (!device.getServiceDataUUID().equals(xiaomiUUID))
		return false;
	
	std::string data = device.getServiceData();
	
	return data[2] == 0xE1 && data[3] == 0x4;
}

CubeFinder::CubeFinder()
{
	
}

void CubeFinder::scan(int duration, bool active, int interval, int window)
{
	BLEScan* scanner = BLEDevice::getScan();
	found = false;
	scanner->clearResults();
	scanner->setActiveScan(active); //active scan uses more power, but get results faster
	scanner->setInterval(interval);
	scanner->setWindow(window);  // less or equal setInterval value
	BLEScanResults foundDevices = scanner->start(duration, false);
	
	for (int i = 0; i < foundDevices.getCount(); i++)
	{
		BLEAdvertisedDevice foundDevice = foundDevices.getDevice(i);
		if (isCube(foundDevice))
		{
			cube = foundDevice;
			found = true;
			break;
		}
	}
}

BLEAdvertisedDevice CubeFinder::getCubeDevice()
{
	return cube;
}

bool CubeFinder::isCubeFound()
{
	return found;
}

void CubeFinder::clear()
{
	BLEScan* scanner = BLEDevice::getScan();
	scanner->clearResults();
}

CubeFinder::~CubeFinder()
{
	clear();
}