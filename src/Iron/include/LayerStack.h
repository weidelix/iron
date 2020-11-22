#pragma once

#include "pch.h"
#include "Core.h"
#include "Layer.h"

namespace Iron
{
	class IRON_API LayerStack
	{
	private:
		std::vector<Layer*> m_layers;
		unsigned int m_layerIndex = 0;
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	};
}