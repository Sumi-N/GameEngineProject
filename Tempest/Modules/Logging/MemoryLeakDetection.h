#pragma once

#include "Define.h"

/* Defines global operator new to allocate from
/* client blocks*/
#ifdef _DEBUG
#define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define DEBUG_NEW
#endif // _DEBUG
/* Compile options needed: /Zi /D_DEBUG /MLd
/* or use a
/* Default Workspace for a Console Application to
/* build a Debug version*/
#include "crtdbg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MEMORY_LEAK_DETECTION\
	{\
		int _flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);\
		_flag |= _CRTDBG_LEAK_CHECK_DF;\
		_CrtSetDbgFlag(_flag);\
	}