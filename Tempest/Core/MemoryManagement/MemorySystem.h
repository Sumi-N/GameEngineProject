#pragma once
#include "FixedSizeAllocator.h"
#include "HeapManager.h"

static HeapManager generalmanager;
static FixedSizeAllocator allocator[4];
static bool IsHeapInitialized{false};

void InitializeMemorySystem(void* i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

bool IsHeapAlive();

void DestroyMemorySystem();

void* AllocMemory(size_t i_size);

void* ReallocMemory(void* i_ptr, size_t i_size);

void FreeMemory(void* i_ptr);

void Collect();