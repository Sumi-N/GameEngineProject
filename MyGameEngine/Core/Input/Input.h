#pragma once
#include "Define.h"

enum class InputState : uint8_t
{
	Released  = 0,
	Pressed   = 1,
	Releasing = 2,
	Pressing  = 3,
};

class Input
{
public:
	float X(){return xpos;}
	float Y(){return ypos;}
	float MouseVelocityX(){return xpos - past_xpos; }
	float MouseVelocityY(){return ypos - past_ypos; }

	void Init();
	InputState QueryKey(VirtualKey i_VKeyID);

private:
	float xpos = 0, ypos = 0;
	float past_xpos = 0, past_ypos = 0;

	std::unordered_map<VirtualKey, bool> state;
	std::unordered_map<VirtualKey, bool> paststate;
	std::vector<std::pair<VirtualKey, bool>> pastkeys;

#ifdef ENGINE_PLATFORM_WINDOWS

public:
	bool IsKeyPressed(VirtualKey);
	bool IsKeyReleased(VirtualKey);
	void Populate();

#endif // ENGINE_PLATFORM_WINDOWS

};




