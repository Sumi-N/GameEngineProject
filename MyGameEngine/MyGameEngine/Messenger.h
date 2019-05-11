#pragma once
#include "Delegates.h"

namespace System {
	class Messenger {
	public:
		static Engine::MultiCastDelegate<int> * LogMessenger;
		static void Init();
		static void BroadCastMessages();
		static void Release();
	};
}

inline void System::Messenger::Init() {
	LogMessenger = new Engine::MultiCastDelegate<int>();
}

inline void System::Messenger::BroadCastMessages() {
	LogMessenger->ExecuteOnBound(0);
}

inline void System::Messenger::Release() {
	delete LogMessenger;
}