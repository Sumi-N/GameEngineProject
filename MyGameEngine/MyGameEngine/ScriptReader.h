#pragma once
//#include "DebugLog.h"
#include "Object3D.h"
#include "EntityMaster.h"

#include <assert.h>

#define FILEPTH "..\\Assets\\editabledatas\\"

namespace System {
	class ScriptReader {
	public:
		static Object3D * CreateActor(const char *);

	private:

	};
}
