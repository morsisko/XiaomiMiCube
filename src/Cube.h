#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>
#include <BLEAdvertisedDevice.h>

static BLEUUID serviceUUID("0000fe95-0000-1000-8000-00805f9b34fb"); //xiaomi uuid
static BLEUUID realUUID("0000aadb-0000-1000-8000-00805f9b34fb"); //service uuid
static BLEUUID ReadWriteServiceUUID("0000aaaa-0000-1000-8000-00805f9b34fb");

static BLEUUID charUUID("0000aadc-0000-1000-8000-00805f9b34fb"); //characteristic uuid
static BLEUUID writeUUID("0000aaac-0000-1000-8000-00805f9b34fb");
static BLEUUID readUUID("0000aaab-0000-1000-8000-00805f9b34fb");

class Cube;
typedef void (*MovedCallback)(Cube*, uint8_t);
typedef void (*SolvedCallback)(Cube*);

class Cube : public BLERemoteCharacteristicCallbacks
{
private:
	static const uint8_t SYS_CMD_GET_BATTERY = 0xB5;
	static const uint8_t SYS_CMD_GET_UID = 0xBA;
	static const uint8_t SYS_CMD_GET_SOFTWARE_VERSION = 0xB7;
	static const uint8_t SYS_CMD_GET_ALL_STEP = 0xCC;

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
	
	
	enum MoveCode
	{
		UNKNOWN,
		MOVE_R = 0x51,
		MOVE_R_ = 0x53,
		MOVE_L = 0x31,
		MOVE_L_ = 0x33,
		MOVE_U = 0x41,
		MOVE_U_ = 0x43,
		MOVE_D = 0x21,
		MOVE_D_ = 0x23,
		MOVE_F = 0x61,
		MOVE_F_ = 0x63,
		MOVE_B = 0x11,
		MOVE_B_ = 0x13,
	};
	
	static char* moveToString(MoveCode code);
};