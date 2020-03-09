#pragma once

#include <Core/Time/Time.h>
#include <Core/EntitySystem/Entity.h>

#include <Graphics/Graphic.h>


/////////////// Global variables
#include "Thread.h"
#include "GameThread.h"
#include "RenderThread.h"

GameThread Thread_Game;
RenderThread Thread_Render;
