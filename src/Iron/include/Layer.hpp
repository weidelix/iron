#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Event/Event.hpp"

namespace Iron
{
	class IRON_API Layer
	{
	protected:
		std::string m_debugName;
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Iron::Event& event) { }

		const std::string& GetName() const { return m_debugName; }
	};
}