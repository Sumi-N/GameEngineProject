#pragma once
#include "Define.h"

/////////////// Global variables
#include "Thread.h"
#include "GameThread.h"
#include "RenderThread.h"

GameThread Thread_Game;
RenderThread Thread_Render;

//Data required for render thread
GraphicRequiredData  container_render[2];
GraphicRequiredData* data_game_own = &container_render[0];
GraphicRequiredData* data_render_own = &container_render[1];

Input UserInput;

std::vector<std::pair<unsigned int, bool>> input_update_list[2];
std::vector<std::pair<unsigned int, bool>>* input_update_list_game_own = &input_update_list[0];
std::vector<std::pair<unsigned int, bool>>* input_update_list_render_own = &input_update_list[1];

