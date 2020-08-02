#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>

class Thread
{
public:
	static std::mutex Mutex_Game;
	static std::mutex Mutex_Render;

	static std::condition_variable Condition_Game;
	static std::condition_variable Condition_Render;

	static bool b_game_ready;
	static bool b_render_ready;

	virtual void Boot(){};
	virtual void Init(){};
	virtual void Run(){};
	virtual void CleanUp(){};
	virtual void Eject(){};

	virtual void WriteDataToOwningThread(){};
};

