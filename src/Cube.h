#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>
#include <BLEAdvertisedDevice.h>

static BLEUUID realUUID("0000aadb-0000-1000-8000-00805f9b34fb");
static BLEUUID charUUID("0000aadc-0000-1000-8000-00805f9b34fb");
static BLEUUID serviceUUID("0000fe95-0000-1000-8000-00805f9b34fb");

class Cube;
typedef void (*MovedCallback)(Cube* cube);
typedef void (*SolvedCallback)(Cube* cube);

class Cube : public BLERemoteCharacteristicCallbacks
{
private:
	static const uint8_t encodingData[];
	static const uint8_t solvedState[];
	
	uint8_t currentRawState[20] = {0};
	BLEClient* pClient;
	MovedCallback onMove;
	SolvedCallback onSolve;
	
	void onNotify(BLERemoteCharacteristic* pBLERemoteCharacteristic, uint8_t* pData, size_t length, bool isNotify) override;
	void decodeMovePacket(const uint8_t* packet);
	
public:
	Cube();
	void connect(BLEAdvertisedDevice device);
	void setOnMove(MovedCallback onMove);
	void setOnSolve(SolvedCallback onSolve);
	bool isSolved();
};