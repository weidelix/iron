#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Event/Event.hpp"

namespace Iron
{
	class IRON_API Layer
	{
	protected:
		string m_debugName;
	public:
		Layer(const string& debugName = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Iron::Event& event) { }

		const string& GetName() const { return m_debugName; }
	};
}