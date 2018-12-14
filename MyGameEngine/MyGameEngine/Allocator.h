#pragma once
#include "HeapManager.h"
#include "DebugLog.h"
#include <Windows.h>
#include <iostream>
#include <assert.h>

const size_t 		sizeHeap = 1024 * 1024;
const unsigned int 	numDescriptors = 2048;

// Allocate memory for my test heap.
void * pHeapMemory = HeapAlloc(GetProcessHeap(), 0, sizeHeap);

// Create a heap manager for my test heap.
HeapManager * pHeapManager = HeapManager::create(pHeapMemory, sizeHeap, numDescriptors);

void *operator new(size_t i_size) {
	void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHeapManager->_alloc(i_size, 4)) + sizeof(Using));
	//assert(pHeapManager->_alloc(i_size, 4));
	return rtnp;
}

void * operator new[](size_t i_size) {
	void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHeapManager->_alloc(i_size, 4)) + sizeof(Using));
	//assert(pHeapManager->_alloc(i_size, 4));
	return rtnp;
}

void operator delete(void * iptr) {
	void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(iptr) - sizeof(Using));
	pHeapManager->_free(rtnp);
	DEBUG_PRINT("normeal delete");
	return;
}

void operator delete[](void * iptr) {
	void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(iptr) - sizeof(Using));
	pHeapManager->_free(rtnp);
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void * operator new(size_t i_size, HeapManager * pHeap) {
	void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHeap->_alloc(i_size, 4)) + sizeof(Using));
	//assert(pHeap->_alloc(i_size, 4));
	DEBUG_PRINT("iwas called");
	return rtnp;
}

void * operator new[](size_t i_size, HeapManager * pHeap) {
	void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pHeap->_alloc(i_size, 4)) + sizeof(Using));
	//assert(pHeap->_alloc(i_size, 4));
	return rtnp;
}

void operator delete(void * iptr, HeapManager * pHeap) {
	void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(iptr) - sizeof(Using));
	pHeap->_free(rtnp);
	DEBUG_PRINT("special delete");
	return;
}

void operator delete[](void * iptr, HeapManager * pHeap) {
	void * rtnp = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(iptr) - sizeof(Using));
	pHeap->_free(rtnp);
	return;
}