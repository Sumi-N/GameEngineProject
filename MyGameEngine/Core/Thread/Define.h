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
extern HWND WindowsHanlder;
