#pragma once

// Configuration
#include <Configuration/Configuration.h>
// Time
#include <Core/Time/Time.h>
// Memory Management
#include <Core/MemoryManagement/MemorySystem.h>
// Entity System
#include <Core/EntitySystem/Entity.h>
// Thread
#include <Core/Thread/Thread.h>
// Input
#include <Core/Input/Input.h>
#include <Core/Input/Event.h>
#include <Core/Input/MouseEvent.h>
#include <Core/Input/KeyEvent.h>
#include <Core/Input/ApplicationEvent.h>

#include <functional>
#include <Layer/LayerStack.h>

#include <Graphics/Graphic.h>
#include <Graphics/ConstantBuffer.h>

#include <Input/Delegate.h>

extern Input UserInput;

// Logging
// Put MemoryLeakDetection in the last since there is a macro #define new DEBUG_NEW
// which might overwrite new keywords exist in the other libraries 
#include <Logging/MemoryLeakDetection.h>
