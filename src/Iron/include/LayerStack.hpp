#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Layer.hpp"

namespace Iron
{
	class IRON_API LayerStack
	{
	private:
		vector<Layer*> m_layers;
		unsigned int m_layerIndex = 0;
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		vector<Layer*>::iterator begin() { return m_layers.begin(); }
		vector<Layer*>::iterator end() { return m_layers.end(); }

	};
}