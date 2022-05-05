#include "LayerStack.h"

namespace Tempest
{
	std::vector<Layer*> LayerStack::Layers{};
	unsigned int LayerStack::insert_index;

	LayerStack::~LayerStack()
	{
		for (auto layer : Layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* i_layer)
	{		
		Layers.emplace(Layers.begin() + insert_index, i_layer);
		insert_index++;
	}

	void LayerStack::PushOverlay(Layer* i_layer)
	{
		i_layer->OnAttach();
		Layers.emplace_back(i_layer);
	}

	void LayerStack::PopLayer(Layer* i_layer)
	{
		auto it = std::find(Layers.begin(), Layers.begin() + insert_index, i_layer);
		if (it != Layers.begin() + insert_index)
		{
			i_layer->OnDetach();
			Layers.erase(it);
			insert_index--;
		}
	}

	void LayerStack::Init()
	{
		for (Layer* layer : Layers)
		{
			layer->OnAttach();
		}
	}

	void LayerStack::Update()
	{
		for (Layer* layer : Layers)
		{
			layer->OnUpdate();
		}
	}

	void LayerStack::OnCriticalSection()
	{
		for (Layer* layer : Layers)
		{
			layer->OnCriticalSection();
		}
	}

	void LayerStack::OnEvent(Event& i_event)
	{
		for (auto layer : Layers)
		{
			layer->OnEvent(i_event);
		}
	}

	void LayerStack::CleanUp()
	{
		for (auto layer : Layers)
		{
			layer->OnDetach();
		}
	}
}