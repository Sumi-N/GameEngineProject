#pragma once
#include "Define.h"

namespace Tempest
{

	class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};		
		virtual void OnBoot() {};
		virtual void OnCriticalSection() {};

		virtual void OnEvent(Event& event) {};
	};

}