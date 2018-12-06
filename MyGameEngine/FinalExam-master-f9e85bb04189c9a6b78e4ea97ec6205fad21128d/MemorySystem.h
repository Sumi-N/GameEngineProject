#pragma once
#include "FixedSizeAllocator.h"
#include "NewHeapManager.h"

// InitializeMemorySystem - initialize your memory system including your HeapManager and some FixedSizeAllocators
bool InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory, unsigned int i_OptionalNumDescriptors);

static NewHeapManager normalmanager;
static FixedSizeAllocator allocator[3];
static void * p_fixedallocator[3];

// Collect - coalesce free blocks in attempt to create larger blocks
void Collect();

// DestroyMemorySystem - destroy your memory systems
void DestroyMemorySystem();

void * AllocMemory(size_t size);

void FreeMemory(void * i_ptr);
