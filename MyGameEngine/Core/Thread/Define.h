#pragma once

#include <Core/Time/Time.h>
#include <Core/EntitySystem/Entity.h>
#include <Core/Input/Input.h>

#include <Graphics/Graphic.h>
#include <Graphics/ConstantBuffer.h>

extern class GameThread Thread_Game;
extern class RenderThread Thread_Render;

extern GraphicRequiredData* data_game_own;
extern GraphicRequiredData* data_render_own;

extern Input UserInput;

extern std::vector<std::pair<unsigned int, bool>>* input_update_list_game_own;
extern std::vector<std::pair<unsigned int, bool>>* input_update_list_render_own;

//////////////// For Input
#ifdef ENGINE_GRAPHIC_OPENGL
#include <../APIs/GraphicAPI/glew-2.1.0/include/GL/glew.h>
#include <../APIs/GraphicAPI/glfw-3.3.bin.WIN32/include/GLFW/glfw3.h>
#endif // ENGINE_GRAPHIC_OPENGL
