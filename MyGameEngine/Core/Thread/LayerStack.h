#pragma once
#include "Define.h"
#include "Layer.h"

class LayerStack
{
public:
	LayerStack() = default;
	~LayerStack();

	void PushLayer(Layer*);
	void PushOverlay(Layer*);
	void PopLayer(Layer*);
	void CleanUp();

	std::vector<Layer*> Layers();
private:
	std::vector<Layer *> layers;
	unsigned int insert_index = 0;
};
