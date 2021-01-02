#pragma once

#include "Layer.hpp"

namespace Iron
{
	class Viewport : public Layer
	{
	private: 

	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
	};
}