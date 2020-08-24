#pragma once
#include "Define.h"

/////////////// Global variables
#include "GameThread.h"
#include "RenderThread.h"

GameThread Thread_Game;
RenderThread Thread_Render;

//Data required for render thread
GraphicRequiredData  container_render[2];
GraphicRequiredData* data_game_own = &container_render[0];
GraphicRequiredData* data_render_own = &container_render[1];

Input UserInput;
HWND WindowsHanlder;
Window * window;


