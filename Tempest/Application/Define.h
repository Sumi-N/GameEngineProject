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
// Graphics
#include <Graphics/Graphic.h>
#include <Graphics/ConstantBuffer.h>

#include <functional>
// UserInterface
#include <UserInterface/ImguiLayer.h>

extern Input UserInput;

// Logging
// Put MemoryLeakDetection in the last since there is a macro #define new DEBUG_NEW
// which might overwrite new keywords that exist in other libraries 
#include <Logging/MemoryLeakDetection.h>

