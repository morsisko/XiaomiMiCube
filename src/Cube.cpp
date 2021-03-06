#include "Cube.h"
#include <Arduino.h>

const uint8_t Cube::encodingData[] = {80, 175, 152, 32, 170, 119, 19, 137, 218, 230, 63, 95, 46, 130, 106, 175, 163, 243, 20, 7, 167, 21, 168, 232, 143, 175, 42, 125, 126, 57, 254, 87, 217, 91, 85, 215};
const uint8_t Cube::solvedState[] = {0x12, 0x34, 0x56, 0x78, 0x33, 0x33, 0x33, 0x33, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0x00, 0x00};


void Cube::onMoveNotify(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify)
{
	if (length != 20)
		return;
	
	if (pData[18] != 0xA7)
		return;
	
	decodeMovePacket(pData);
	
	if (onMove)
		onMove(this, currentRawState[16]);
	
	if (onSolve && isSolved())
		onSolve(this);
}

void Cube::onSettingsNotify(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify)
{
	parseSettingsData(pData, length);
}

Cube::Cube()
{
	onMove = nullptr;
	onSolve = nullptr;
	pClient = nullptr;
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
	
	subscribeForMoveNotifications();
	subscribeForSettingsNotifications();
}

void Cube::subscribeForMoveNotifications()
{
	BLERemoteService* pRemoteService = pClient->getService(moveServiceUUID);
	
    if (pRemoteService == nullptr) {
      pClient->disconnect();
      return;
    }
	
    BLERemoteCharacteristic* pRemoteCharacteristic = pRemoteService->getCharacteristic(moveCharUUID);
    if (pRemoteCharacteristic == nullptr) {
      pClient->disconnect();
      return;
    }
	
    if(pRemoteCharacteristic->canNotify())
    {
	  pRemoteCharacteristic->registerForNotify(std::bind(&Cube::onMoveNotify, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    }
}

void Cube::subscribeForSettingsNotifications()
{
	BLERemoteService* pRemoteService = pClient->getService(readWriteServiceUUID);
	
    if (pRemoteService == nullptr) {
      pClient->disconnect();
      return;
    }
	
	writeCharacteristic = pRemoteService->getCharacteristic(writeUUID);
    BLERemoteCharacteristic* readCharacteristic = pRemoteService->getCharacteristic(readUUID);
    if (readCharacteristic == nullptr || writeCharacteristic == nullptr) {
      pClient->disconnect();
      return;
    }
	
    if(readCharacteristic->canNotify())
    {
	  readCharacteristic->registerForNotify(std::bind(&Cube::onSettingsNotify, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    }
}

void Cube::requestTotalMoves()
{
	if (writeCharacteristic)
	writeCharacteristic->writeValue(SYS_CMD_GET_ALL_STEP);
}

void Cube::requestBattery()
{
	if (writeCharacteristic)
	writeCharacteristic->writeValue(SYS_CMD_GET_BATTERY);
}

void Cube::requestUid()
{
	if (writeCharacteristic)
	writeCharacteristic->writeValue(SYS_CMD_GET_UID);
}

void Cube::requestSoftVersion()
{
	if (writeCharacteristic)
	writeCharacteristic->writeValue(SYS_CMD_GET_SOFTWARE_VERSION);
}

void Cube::requestAllProperties()
{
	requestTotalMoves();
	requestBattery();
	requestUid();
	requestSoftVersion();
}

const CubeState& Cube::getState()
{
	cubeState.update(currentRawState);
	return cubeState;
}

void Cube::parseSettingsData(const uint8_t* packet, int len)
{
	uint8_t cmd = packet[0];
	
	if (cmd == SYS_CMD_GET_ALL_STEP && len >= 5)
	{
		totalMoves = packet[1];
		totalMoves <<= 8;
		totalMoves |= packet[2];
		totalMoves <<= 8;
		totalMoves |= packet[3];
		totalMoves <<= 8;
		totalMoves |= packet[4];
	}
	
	else if (cmd == SYS_CMD_GET_UID && len >= 7)
	{
		for (int i = 0; i < 6; i++)
			uid[i] = packet[i + 1];
	}
	
	else if (cmd == SYS_CMD_GET_BATTERY && len >= 3)
	{
		uint8_t adcValue = packet[1];
		if (adcValue >= 170)
			batteryVoltage = 4.5f;
		
		else if (adcValue < 120)
			batteryVoltage = 3.0f;
		
		adcValue -= 120;
		
		batteryVoltage = 3.0f + (1.5f * adcValue/50.f);
	}
	
	else if (cmd == SYS_CMD_GET_SOFTWARE_VERSION && len >= 8)
	{
		for (int i = 0; i < 7; i++)
			softVersion[i] = packet[i + 1];
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

bool Cube::isConnected()
{
	if (!pClient)
		return false;
	
	pClient->isConnected();
}

char* Cube::moveToString(MoveCode code)
{
	if (code == MOVE_R )
		return "R";
	if (code == MOVE_R_)
		return "R'";
	if (code == MOVE_L )
		return "L";
	if (code == MOVE_L_)
		return "L'";
	if (code == MOVE_U )
		return "U";
	if (code == MOVE_U_)
		return "U'";
	if (code == MOVE_D )
		return "D";
	if (code == MOVE_D_)
		return "D'";
	if (code == MOVE_F )
		return "F";
	if (code == MOVE_F_)
		return "F'";
	if (code == MOVE_B )
		return "B";
	if (code == MOVE_B_)
		return "B'";
	
	return "?";
}

uint32_t Cube::getTotalMoves()
{
	return totalMoves;
}

float Cube::getBatteryVoltage()
{
	return batteryVoltage;
}

uint8_t* Cube::getUid()
{
	return uid;
}

uint8_t* Cube::getSoftVersion()
{
	return softVersion;
}