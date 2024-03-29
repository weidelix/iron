#include "LayerStack.hpp"

namespace Iron
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_layerIndex, layer);
		layer->OnAttach();
      m_layerIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
      overlay->OnAttach();
	}
	
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = find(m_layers.begin(), m_layers.end(), layer);

		// if layer is not the last layer in the stack
		if (it != m_layers.begin() + m_layerIndex)
		{
			layer->OnDetach();
			m_layers.erase(it);
			m_layerIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			overlay->OnDetach();
			m_layers.erase(it);
		}
	}
}