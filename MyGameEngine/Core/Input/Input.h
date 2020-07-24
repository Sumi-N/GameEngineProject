#pragma once
#include "Define.h"

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




