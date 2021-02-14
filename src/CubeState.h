#include <cinttypes>

class CubeState
{
private:
	uint8_t cube[55];
	
	void ConverseToPaperType(uint8_t raw[20]);
	uint32_t ConverseAngleSetXfirst(uint8_t angle, uint8_t angleFace, uint8_t f1, uint8_t f2, uint8_t f3);
	uint32_t ConverseAngleSetSingleXfirst(uint8_t angleFace, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t c1, uint8_t c2, uint8_t c3);
	uint32_t ConverseAngleSetYfirst(uint8_t angle, uint8_t angleFace, uint8_t f1, uint8_t f2, uint8_t f3);
	uint32_t ConverseAngleSetSingleYfirst(uint8_t angleFace, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t c1, uint8_t c2, uint8_t c3);
	uint32_t ConverseLineSet(uint8_t line, uint8_t lineFace, uint8_t p1, uint8_t p2);
	uint32_t ConverseLineSetSingle(uint8_t lineFace, uint8_t p1, uint8_t p2, uint8_t c1, uint8_t c2);
	void ConverseChangeFaceAgain(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4);
public:
	CubeState();
	void update(uint8_t raw[20]);
	uint8_t get(uint8_t index) const;
	
	enum Color
	{
		INVALID = 0,
		GREEN = 1,
		YELLOW = 2,
		RED = 3,
		WHITE = 4,
		ORANGE = 5,
		BLUE = 6
	};
	
	static char* colorToString(Color color);
};