#pragma once
#include "Define.h"
#include "Layer.h"

namespace Tempest
{

	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		static void PushLayer(Layer*);
		static void PushOverlay(Layer*);
		static void PopLayer(Layer*);
		static void Boot();
		static void Update();
		static void OnEvent(Event&);
		static void CleanUp();		

		//static Array<Layer*> Layers();
	private:
		static std::vector<Layer*> Layers;
		static unsigned int insert_index;
	};

}
