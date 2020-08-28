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

}