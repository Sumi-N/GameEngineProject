#pragma once
#include "FixedSizeAllocator.h"
#include "HeapManager.h"

extern HeapManager GeneralManager;
//extern FixedSizeAllocator allocator[4];

bool IsHeapAlive();

void* AllocMemory(size_t i_size);

void* ReallocMemory(void* i_ptr, size_t i_size);

void FreeMemory(void* i_ptr);