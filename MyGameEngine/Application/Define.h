#pragma once

// Configuration
#include <Configuration/Configuration.h>
// Time
#include <Core/Time/Time.h>
// Entity System
#include <Core/EntitySystem/Entity.h>
// Thread
#include <Core/Thread/Thread.h>
// Input
#include <Core/Input/Input.h>
#include <Core/Input/Event.h>
#include <Core/Input/MouseEvent.h>
#include <Core/Input/KeyEvent.h>
#include <Core/INput/ApplicationEvent.h>
// Logging
#include <Logging/MemoryLeakDetection.h>
// Graphics
#include <Graphics/Graphic.h>
#include <Graphics/ConstantBuffer.h>

#include <functional>

extern GraphicRequiredData* data_game_own;
extern GraphicRequiredData* data_render_own;

extern Input UserInput;
extern HWND WindowsHanlder;

