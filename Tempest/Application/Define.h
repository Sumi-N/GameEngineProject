#pragma once

// Configuration
#include <Configuration/Configuration.h>
// Time
#include <Core/Time/Time.h>
// Memory Management
#include <Core/MemoryManagement/MemorySystem.h>
// Entity System
#include <EntitySystem/Entity.h>
// Thread
#include <Core/Thread/Thread.h>
// Input
#include <Core/Input/Input.h>
#include <Core/Input/Event.h>
#include <Core/Input/MouseEvent.h>
#include <Core/Input/KeyEvent.h>
#include <Core/Input/ApplicationEvent.h>

#include <Layer/LayerStack.h>

#include <Graphics/Window.h>
#include <Graphics/ConstantBuffer.h>

#include <Rendering/Framework.h>

#include <Input/Delegate.h>

extern Tempest::Input UserInput;

// Logging
// Place MemoryLeakDetection header at the last or the macro #define new DEBUG_NEW
// might overwrite new keywords exist in the other libraries
#include <Logging/MemoryLeakDetection.h>
