#pragma once
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

class RenderEngine{
public:
	void TestKeyCallback(unsigned int, bool);
};

inline void RenderEngine::TestKeyCallback(unsigned int i_VKeyID, bool bWentDown) {
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	//sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	sprintf_s(Buffer, lenBuffer, "VKey %d went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

