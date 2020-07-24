#pragma once
#include "Define.h"
#include <unordered_map>
#include <vector>
#include <utility>

enum class VirtualKey : unsigned int
{
	KEY_LEFTBUTTON = 0x01,
	KEY_RIGHTBUTTON = 0x02,
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

enum class InputState : uint8_t
{
	Released  = 0,
	Pressed   = 1,
	Releasing = 2,
	Pressing  = 3,
};

struct InputFormat
{
	float x; float y;
	std::vector<std::pair<VirtualKey, bool>> keys;
};

class Input
{
public:
	float X(){return xpos;}
	float Y(){return ypos;}
	float MouseVelocityX(){return xpos - past_xpos; }
	float MouseVelocityY(){return ypos - past_ypos; }

	void Init();
	void QueryInputs();
	void Populate(InputFormat & i_input);
	InputState QueryKey(VirtualKey i_VKeyID);

private:
	float xpos, ypos;
	float past_xpos, past_ypos;

	std::unordered_map<VirtualKey, bool> state;
	std::unordered_map<VirtualKey, bool> paststate;
	std::vector<std::pair<VirtualKey, bool>> pastkeys;
};

inline void Input::Init()
{
	for (int i = 0; i < 256; i++)
	{
		state.insert({ static_cast<VirtualKey>(i), false });
		paststate.insert({ static_cast<VirtualKey>(i), false });
	}

	xpos = 0; ypos = 0;
	past_xpos = 0; past_ypos = 0;
}

inline void Input::Populate(InputFormat & i_input)
{
	if (i_input.x != -1 && i_input.y != -1)
	{
		past_xpos = xpos; past_ypos = ypos;
		xpos = i_input.x; ypos = i_input.y;
	}
	else
	{
		past_xpos = xpos; past_ypos = ypos;
	}

	for (auto& ele : pastkeys)
	{
		paststate.at(ele.first) = state.at(ele.first);
	}

	for (auto& ele : i_input.keys)
	{
		state.at(ele.first) = ele.second;
   	}

	// Copy the keys for resetting past input state
	pastkeys = i_input.keys;

	// Reset input format data
	i_input.keys.clear();
	i_input.x = -1; i_input.y = -1;
}

inline InputState Input::QueryKey(VirtualKey i_VKeyID)
{
	if (state.at(i_VKeyID) == true)
	{
		if (paststate.at(i_VKeyID) == true)
		{
			return InputState::Pressing;
		}
		else
		{
			return InputState::Pressed;
		}
	}
	else
	{
		if (paststate.at(i_VKeyID) == true)
		{
			return InputState::Released;
		}
		else
		{
			return InputState::Releasing;
		}
	}
}




