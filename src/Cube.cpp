#include "Cube.h"
#include <Arduino.h>

Cube* mainCube;

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    
    Serial.print("Moved");

}

Cube::Cube()
{
	mainCube = this;
}

void Cube::connect(BLEAdvertisedDevice device)
{
	pClient = BLEDevice::createClient();
	pClient->connect(&device);
	BLERemoteService* pRemoteService = pClient->getService(realUUID);
	
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();
      return;
    }
	
    BLERemoteCharacteristic* pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect();
      return;
    }
	
    if(pRemoteCharacteristic->canNotify())
    {
      pRemoteCharacteristic->registerForNotify(notifyCallback);
	  Serial.println("Registered callback!");
    }
	else
	{
		Serial.println("Registration failed!");
	}
}