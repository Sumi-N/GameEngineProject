#include "Thread.h"

std::mutex Thread::Mutex_Game;
std::mutex Thread::Mutex_Render;

std::condition_variable Thread::Condition_Game;
std::condition_variable Thread::Condition_Render;

bool Thread::b_game_ready;
bool Thread::b_render_ready;