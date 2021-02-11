#include "CubeState.h"

CubeState::CubeState()
{
	
}

void CubeState::update(uint8_t raw[20])
{
	for (uint8_t i = 0; i < sizeof(cube) / sizeof(uint8_t); i++)
		cube[i] = 0;
	
	ConverseToPaperType(raw);
}

void CubeState::ConverseToPaperType(uint8_t raw[20])
{
	uint32_t num = 0;
	uint8_t array2[8] = {0};
	uint8_t array3[8] = {0};
	uint8_t array4[12] = {0};
	uint8_t array5[12] = {0};


	array2[0] = raw[0] >> 4;
	array2[1] = raw[0] & 15;
	array2[2] = raw[1] >> 4;
	array2[3] = raw[1] & 15;
	array2[4] = raw[2] >> 4;
	array2[5] = raw[2] & 15;
	array2[6] = raw[3] >> 4;
	array2[7] = raw[3] & 15;
	array3[0] = raw[4] >> 4;
	array3[1] = raw[4] & 15;
	array3[2] = raw[5] >> 4;
	array3[3] = raw[5] & 15;
	array3[4] = raw[6] >> 4;
	array3[5] = raw[6] & 15;
	array3[6] = raw[7] >> 4;
	array3[7] = raw[7] & 15;
	array4[0] = raw[8] >> 4;
	array4[1] = raw[8] & 15;
	array4[2] = raw[9] >> 4;
	array4[3] = raw[9] & 15;
	array4[4] = raw[10] >> 4;
	array4[5] = raw[10] & 15;
	array4[6] = raw[11] >> 4;
	array4[7] = raw[11] & 15;
	array4[8] = raw[12] >> 4;
	array4[9] = raw[12] & 15;
	array4[10] = raw[13] >> 4;
	array4[11] = raw[13] & 15;
	
	for (uint8_t b = 0; b < 12; b += 1)
	{
		array5[b] = 0;
	}
	if ((raw[14] & 128) != 0)
	{
		array5[0] = 2;
	}
	else
	{
		array5[0] = 1;
	}
	if ((raw[14] & 64) != 0)
	{
		array5[1] = 2;
	}
	else
	{
		array5[1] = 1;
	}
	if ((raw[14] & 32) != 0)
	{
		array5[2] = 2;
	}
	else
	{
		array5[2] = 1;
	}
	if ((raw[14] & 16) != 0)
	{
		array5[3] = 2;
	}
	else
	{
		array5[3] = 1;
	}
	if ((raw[14] & 8) != 0)
	{
		array5[4] = 2;
	}
	else
	{
		array5[4] = 1;
	}
	if ((raw[14] & 4) != 0)
	{
		array5[5] = 2;
	}
	else
	{
		array5[5] = 1;
	}
	if ((raw[14] & 2) != 0)
	{
		array5[6] = 2;
	}
	else
	{
		array5[6] = 1;
	}
	if ((raw[14] & 1) != 0)
	{
		array5[7] = 2;
	}
	else
	{
		array5[7] = 1;
	}
	if ((raw[15] & 128) != 0)
	{
		array5[8] = 2;
	}
	else
	{
		array5[8] = 1;
	}
	if ((raw[15] & 64) != 0)
	{
		array5[9] = 2;
	}
	else
	{
		array5[9] = 1;
	}
	if ((raw[15] & 32) != 0)
	{
		array5[10] = 2;
	}
	else
	{
		array5[10] = 1;
	}
	if ((raw[15] & 16) != 0)
	{
		array5[11] = 2;
	}
	else
	{
		array5[11] = 1;
	}
	cube[32] = 1;
	cube[41] = 2;
	cube[50] = 3;
	cube[14] = 4;
	cube[23] = 5;
	cube[5] = 6;
	num |= ConverseAngleSetXfirst(array2[0], array3[0], 34, 43, 54);
	num |= ConverseAngleSetYfirst(array2[1], array3[1], 36, 52, 18);
	num |= ConverseAngleSetXfirst(array2[2], array3[2], 30, 16, 27);
	num |= ConverseAngleSetYfirst(array2[3], array3[3], 28, 25, 45);
	num |= ConverseAngleSetYfirst(array2[4], array3[4], 1, 48, 37);
	num |= ConverseAngleSetXfirst(array2[5], array3[5], 3, 12, 46);
	num |= ConverseAngleSetYfirst(array2[6], array3[6], 9, 21, 10);
	num |= ConverseAngleSetXfirst(array2[7], array3[7], 7, 39, 19);
	num |= ConverseLineSet(array4[0], array5[0], 31, 44);
	num |= ConverseLineSet(array4[1], array5[1], 35, 53);
	num |= ConverseLineSet(array4[2], array5[2], 33, 17);
	num |= ConverseLineSet(array4[3], array5[3], 29, 26);
	num |= ConverseLineSet(array4[4], array5[4], 40, 51);
	num |= ConverseLineSet(array4[5], array5[5], 15, 49);
	num |= ConverseLineSet(array4[6], array5[6], 13, 24);
	num |= ConverseLineSet(array4[7], array5[7], 42, 22);
	num |= ConverseLineSet(array4[8], array5[8], 4, 38);
	num |= ConverseLineSet(array4[9], array5[9], 2, 47);
	num |= ConverseLineSet(array4[10], array5[10], 6, 11);
	num |= ConverseLineSet(array4[11], array5[11], 8, 20);
	ConverseChangeFaceAgain(1, 7, 9, 3);
	ConverseChangeFaceAgain(4, 8, 6, 2);
	ConverseChangeFaceAgain(37, 19, 10, 46);
	ConverseChangeFaceAgain(38, 20, 11, 47);
	ConverseChangeFaceAgain(39, 21, 12, 48);
	ConverseChangeFaceAgain(40, 22, 13, 49);
	ConverseChangeFaceAgain(41, 23, 14, 50);
	ConverseChangeFaceAgain(42, 24, 15, 51);
	ConverseChangeFaceAgain(43, 25, 16, 52);
	ConverseChangeFaceAgain(44, 26, 17, 53);
	ConverseChangeFaceAgain(45, 27, 18, 54);
	ConverseChangeFaceAgain(34, 28, 30, 36);
	ConverseChangeFaceAgain(31, 29, 33, 35);
	if (num != 0)
	{
		for (uint8_t j = 0; j < 55; j++)
		{
			cube[j] = 0;
		}
	}
}

uint32_t CubeState::ConverseAngleSetXfirst(uint8_t angle, uint8_t angleFace, uint8_t f1, uint8_t f2, uint8_t f3)
{
	uint32_t num = 0;
	if (angle == 1)
	{
		num |= ConverseAngleSetSingleXfirst(angleFace, f1, f2, f3, 1, 2, 3);
	}
	else if (angle == 2)
	{
		num |= ConverseAngleSetSingleXfirst(angleFace, f1, f2, f3, 1, 3, 4);
	}
	else if (angle == 3)
	{
		num |= ConverseAngleSetSingleXfirst(angleFace, f1, f2, f3, 1, 4, 5);
	}
	else if (angle == 4)
	{
		num |= ConverseAngleSetSingleXfirst(angleFace, f1, f2, f3, 1, 5, 2);
	}
	else if (angle == 5)
	{
		num |= ConverseAngleSetSingleXfirst(angleFace, f1, f2, f3, 6, 3, 2);
	}
	else if (angle == 6)
	{
		num |= ConverseAngleSetSingleXfirst(angleFace, f1, f2, f3, 6, 4, 3);
	}
	else if (angle == 7)
	{
		num |= ConverseAngleSetSingleXfirst(angleFace, f1, f2, f3, 6, 5, 4);
	}
	else if (angle == 8)
	{
		num |= ConverseAngleSetSingleXfirst(angleFace, f1, f2, f3, 6, 2, 5);
	}
	else
	{
		num |= 2;
	}
	return num;
}

uint32_t CubeState::ConverseAngleSetSingleXfirst(uint8_t angleFace, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t c1, uint8_t c2, uint8_t c3)
{
	uint32_t result = 0;
	if (angleFace == 1)
	{
		cube[p1] = c3;
		cube[p2] = c1;
		cube[p3] = c2;
	}
	else if (angleFace == 2)
	{
		cube[p1] = c2;
		cube[p2] = c3;
		cube[p3] = c1;
	}
	else if (angleFace == 3)
	{
		cube[p1] = c1;
		cube[p2] = c2;
		cube[p3] = c3;
	}
	else
	{
		result = 1;
	}
	return result;
}

uint32_t CubeState::ConverseAngleSetYfirst(uint8_t angle, uint8_t angleFace, uint8_t f1, uint8_t f2, uint8_t f3)
{
	int32_t num = 0;
	if (angle == 1)
	{
		num |= ConverseAngleSetSingleYfirst(angleFace, f1, f2, f3, 1, 2, 3);
	}
	else if (angle == 2)
	{
		num |= ConverseAngleSetSingleYfirst(angleFace, f1, f2, f3, 1, 3, 4);
	}
	else if (angle == 3)
	{
		num |= ConverseAngleSetSingleYfirst(angleFace, f1, f2, f3, 1, 4, 5);
	}
	else if (angle == 4)
	{
		num |= ConverseAngleSetSingleYfirst(angleFace, f1, f2, f3, 1, 5, 2);
	}
	else if (angle == 5)
	{
		num |= ConverseAngleSetSingleYfirst(angleFace, f1, f2, f3, 6, 3, 2);
	}
	else if (angle == 6)
	{
		num |= ConverseAngleSetSingleYfirst(angleFace, f1, f2, f3, 6, 4, 3);
	}
	else if (angle == 7)
	{
		num |= ConverseAngleSetSingleYfirst(angleFace, f1, f2, f3, 6, 5, 4);
	}
	else if (angle == 8)
	{
		num |= ConverseAngleSetSingleYfirst(angleFace, f1, f2, f3, 6, 2, 5);
	}
	else
	{
		num |= 2;
	}
	return num;
}

uint32_t CubeState::ConverseAngleSetSingleYfirst(uint8_t angleFace, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t c1, uint8_t c2, uint8_t c3)
{
	uint32_t result = 0;
	if (angleFace == 2)
	{
		cube[p1] = c3;
		cube[p2] = c1;
		cube[p3] = c2;
	}
	else if (angleFace == 1)
	{
		cube[p1] = c2;
		cube[p2] = c3;
		cube[p3] = c1;
	}
	else if (angleFace == 3)
	{
		cube[p1] = c1;
		cube[p2] = c2;
		cube[p3] = c3;
	}
	else
	{
		result = 1;
	}
	return result;
}

uint32_t CubeState::ConverseLineSet(uint8_t line, uint8_t lineFace, uint8_t p1, uint8_t p2)
{
	uint32_t num = 0;
	if (line == 1)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 1, 2);
	}
	else if (line == 2)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 1, 3);
	}
	else if (line == 3)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 1, 4);
	}
	else if (line == 4)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 1, 5);
	}
	else if (line == 5)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 2, 3);
	}
	else if (line == 6)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 4, 3);
	}
	else if (line == 7)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 4, 5);
	}
	else if (line == 8)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 2, 5);
	}
	else if (line == 9)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 6, 2);
	}
	else if (line == 10)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 6, 3);
	}
	else if (line == 11)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 6, 4);
	}
	else if (line == 12)
	{
		num |= ConverseLineSetSingle(lineFace, p1, p2, 6, 5);
	}
	else
	{
		num = 4;
	}
	return num;
}

uint32_t CubeState::ConverseLineSetSingle(uint8_t lineFace, uint8_t p1, uint8_t p2, uint8_t c1, uint8_t c2)
{
	uint32_t result = 0;
	if (lineFace == 1)
	{
		cube[p1] = c1;
		cube[p2] = c2;
	}
	else if (lineFace == 2)
	{
		cube[p1] = c2;
		cube[p2] = c1;
	}
	else
	{
		result = 3;
	}
	return result;
}

void CubeState::ConverseChangeFaceAgain(uint8_t a1, uint8_t a2, uint8_t a3, uint8_t a4)
{
	uint8_t num = cube[a4];
	cube[a4] = cube[a3];
	cube[a3] = cube[a2];
	cube[a2] = cube[a1];
	cube[a1] = num;
}

uint8_t CubeState::get(uint8_t index) const
{
	if (index < 1 || index > 54)
		return 0;
	
	return cube[index];
}

char* CubeState::colorToString(Color color)
{
	if (color == WHITE)
		return "WHITE";
	
	if (color == YELLOW)
		return "YELLOW";
	
	if (color == GREEN)
		return "GREEN";
	
	if (color == BLUE)
		return "BLUE";
	
	if (color == RED)
		return "RED";
	
	if (color == ORANGE)
		return "ORANGE";
	
	return "UNKNOWN";	
}