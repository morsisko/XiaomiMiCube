#include "Cube.h"
#include <Arduino.h>

const uint8_t Cube::encodingData[] = {80, 175, 152, 32, 170, 119, 19, 137, 218, 230, 63, 95, 46, 130, 106, 175, 163, 243, 20, 7, 167, 21, 168, 232, 143, 175, 42, 125, 126, 57, 254, 87, 217, 91, 85, 215};
const uint8_t Cube::solvedState[] = {0x12, 0x34, 0x56, 0x78, 0x33, 0x33, 0x33, 0x33, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x00, 0x00};

/*
static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    
    Serial.print("Moved");

}
*/

void Cube::onNotify(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify)
{
	Serial.println("Moved from class!");
	
	if (length != 20)
		return;
	
	if (pData[18] != 0xA7)
		return;
	
	decodeMovePacket(pData);
	
	if (onMove)
		onMove(this);
	
	if (onSolve && isSolved())
		onSolve(this);
}

Cube::Cube()
{
	onMove = nullptr;
	onSolve = nullptr;
}

void Cube::decodeMovePacket(const uint8_t* packet)
{
	uint8_t high = packet[19] >> 4;
	uint8_t low = packet[19] & 0xF;

	for (int i = 0; i < 19; i++)
		currentRawState[i] = packet[i] - encodingData[i + low] - encodingData[i + high];
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
      //pRemoteCharacteristic->registerForNotify(notifyCallback);
	  pRemoteCharacteristic->setCallbacks(this);
	  Serial.println("Registered callback!");
    }
	else
	{
		Serial.println("Registration failed!");
	}
}

void Cube::setOnMove(MovedCallback onMove)
{
	this->onMove = onMove;
}

void Cube::setOnSolve(SolvedCallback onSolve)
{
	this->onSolve = onSolve;
}

bool Cube::isSolved()
{
	for (int i = 0; i < sizeof(solvedState) / sizeof(uint8_t); i++)
	{
		if (currentRawState[i] != solvedState[i])
			return false;
	}
	return true;
}