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
#include <Core/INput/ApplicationEvent.h>

#include <functional>
// UserInterface
#include <UserInterface/ImguiLayer.h>

#include <Graphics/Graphic.h>
#include <Graphics/ConstantBuffer.h>

extern Input UserInput;

// Logging
// Put MemoryLeakDetection in the last since there is a macro #define new DEBUG_NEW
// which might overwrite new keywords exist in the other libraries 
#include <Logging/MemoryLeakDetection.h>


#ifdef ENABLE_CUSTOM_ALLOCATOR
	#define INITIALIZE_HEAP_MANAGER \
		void* pHeapMemory = HeapAlloc(GetProcessHeap(), 0, HEAP_SIZE); \
		InitializeMemorySystem(pHeapMemory, HEAP_SIZE, NUM_DESCRIPTOR);	
#endif // ENABLE_CUSTOM_ALLOCATOR
