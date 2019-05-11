#pragma once
#include "DebugLog.h"

#include <unordered_map>

#include "../GLib/GLib.h"


class InputMap {
public:
	static void RegisterInputMap(unsigned int, bool);
	static void InitInputMap();
	static void SetupCallback();
	static void ClearInputMap();

	static std::unordered_map<unsigned int, bool> * Map;
	static std::list<unsigned int> * DeleteList;

private:
};

std::unordered_map<unsigned int, bool> * InputMap::Map;
std::list<unsigned int> * InputMap::DeleteList;

void InputMap::RegisterInputMap(unsigned int i_VKeyID, bool i_bDown) {
	if (i_bDown) {
		InputMap::Map->at(i_VKeyID) = true;
	}
	else {
		InputMap::Map->at(i_VKeyID * 2) = true;
	}
	InputMap::DeleteList->push_back(i_VKeyID);
}

inline void InputMap::InitInputMap() {
	for (int i = 0; i < 256 * 2; i++) {
		Map->insert({i,false});
	}
	SetupCallback();
}

inline void InputMap::SetupCallback() {
	GLib::SetKeyStateChangeCallback(InputMap::RegisterInputMap);
}

inline void InputMap::ClearInputMap() {
	while (!DeleteList->empty())
	{
		unsigned int tmp = DeleteList->front();
		Map->at(tmp) = false;
		DeleteList->pop_front();
	}
}

/* Those are hex numbers
VK_KEY_0	0x30 ('0')	0
VK_KEY_1	0x31 ('1')	1
VK_KEY_2	0x32 ('2')	2
VK_KEY_3	0x33 ('3')	3
VK_KEY_4	0x34 ('4')	4
VK_KEY_5	0x35 ('5')	5
VK_KEY_6	0x36 ('6')	6
VK_KEY_7	0x37 ('7')	7
VK_KEY_8	0x38 ('8')	8
VK_KEY_9	0x39 ('9')	9
VK_KEY_A	0x41 ('A')	A
VK_KEY_B	0x42 ('B')	B
VK_KEY_C	0x43 ('C')	C
VK_KEY_D	0x44 ('D')	D
VK_KEY_E	0x45 ('E')	E
VK_KEY_F	0x46 ('F')	F
VK_KEY_G	0x47 ('G')	G
VK_KEY_H	0x48 ('H')	H
VK_KEY_I	0x49 ('I')	I
VK_KEY_J	0x4A ('J')	J
VK_KEY_K	0x4B ('K')	K
VK_KEY_L	0x4C ('L')	L
VK_KEY_M	0x4D ('M')	M
VK_KEY_N	0x4E ('N')	N
VK_KEY_O	0x4F ('O')	O
VK_KEY_P	0x50 ('P')	P
VK_KEY_Q	0x51 ('Q')	Q
VK_KEY_R	0x52 ('R')	R
VK_KEY_S	0x53 ('S')	S
VK_KEY_T	0x54 ('T')	T
VK_KEY_U	0x55 ('U')	U
VK_KEY_V	0x56 ('V')	V
VK_KEY_W	0x57 ('W')	W
VK_KEY_X	0x58 ('X')	X
VK_KEY_Y	0x59 ('Y')	Y
VK_KEY_Z	0x5A ('Z')	Z
*/