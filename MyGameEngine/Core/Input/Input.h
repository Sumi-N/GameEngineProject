#pragma once
#include <unordered_map>
#include <vector>
#include <utility>

enum class VirtualKey : unsigned int
{
	KEY_SPACE = 0x20,
	KEY_0 = 0x30,
	KEY_1 = 0x31,
	KEY_2 = 0x32,
	KEY_3 = 0x33,
	KEY_4 = 0x34,
	KEY_5 = 0x35,
	KEY_6 = 0x36,
	KEY_7 = 0x37,
	KEY_8 = 0x38,
	KEY_9 = 0x39,
	KEY_A = 0x41,
	KEY_B = 0x42,
	KEY_C = 0x43,
	KEY_D = 0x44,
	KEY_E = 0x45,
	KEY_F = 0x46,
	KEY_G = 0x47,
	KEY_H = 0x48,
	KEY_I = 0x49,
	KEY_J = 0x4A,
	KEY_K = 0x4B,
	KEY_L = 0x4C,
	KEY_M = 0x4D,
	KEY_N = 0x4E,
	KEY_O = 0x4F,
	KEY_P = 0x50,
	KEY_Q = 0x51,
	KEY_R = 0x52,
	KEY_S = 0x53,
	KEY_T = 0x54,
	KEY_U = 0x55,
	KEY_V = 0x56,
	KEY_W = 0x57,
	KEY_X = 0x58,
	KEY_Y = 0x59,
	KEY_Z = 0x5A,
};

class Input
{
public:
	void Init();
	void Populate(std::vector<std::pair<unsigned int, bool>> i_list);
	bool QueryKey(unsigned int i_VKeyID, bool i_bDown);

	std::unordered_map<unsigned int, bool> state;

private:
};

inline void Input::Init()
{
	for (int i = 0; i < 256 * 2; i++)
	{
		state.insert({ i,false });
	}
}

inline void Input::Populate(std::vector<std::pair<unsigned int, bool>> i_list)
{
	for (auto& ele : i_list)
	{
		state.at(ele.first) = ele.second;
	}
}

inline bool Input::QueryKey(unsigned int i_VKeyID, bool i_bDown)
{
	if (i_bDown)
	{
		if (state.at(i_VKeyID) == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (state.at(i_VKeyID) == false)
		{
			return true;
		}
		else
		{
			return false;
		}
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




