#include "LayerStack.h"

LayerStack::~LayerStack()
{
	for (auto layer : layers)
	{
		layer->OnDetach();
		delete layer;
	}
}

void LayerStack::PushLayer(Layer* i_layer)
{
	layers.emplace(layers.begin() + insert_index, i_layer);
	insert_index++;
}

void LayerStack::PushOverlay(Layer* i_layer)
{
	layers.emplace_back(i_layer);
}

void LayerStack::PopLayer(Layer* i_layer)
{
	auto it = std::find(layers.begin(), layers.begin() + insert_index, i_layer);
	if (it != layers.begin() + insert_index)
	{
		i_layer->OnDetach();
		layers.erase(it);
		insert_index--;
	}
}

std::vector<Layer*> LayerStack::Layers()
{
	if (layers.empty())
	{
		Layer* tmp = new Layer();
		PushLayer(tmp);
	}
	return layers;
}