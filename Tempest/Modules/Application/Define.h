#pragma once

// Configuration
#include <Configuration/Configuration.h>
// Time
#include <Time/Time.h>
// Memory Management
#include <MemoryManagement/MemorySystem.h>
// Entity System
#include <EntitySystem/Entity.h>
// Thread
#include <Thread/Thread.h>
// Input
#include <Input/Input.h>
#include <Input/Event.h>
#include <Input/MouseEvent.h>
#include <Input/KeyEvent.h>
#include <Input/ApplicationEvent.h>

#include <Layer/LayerStack.h>

#include <Graphics/Window.h>
#include <Graphics/ConstantBuffer.h>

#include <Rendering/GraphicsFramework.h>

#include <Input/Delegate.h>

extern Tempest::Input UserInput;

// Logging
// Place MemoryLeakDetection header at the last or the macro #define new DEBUG_NEW
// might overwrite new keywords exist in the other libraries
#include <Logging/MemoryLeakDetection.h>
