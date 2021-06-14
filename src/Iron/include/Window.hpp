#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Event/Event.hpp"
#include <GLFW/glfw3.h>

namespace Iron
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProps(std::string t = "Iron", unsigned int w = 800, unsigned int h = 480)
			:Title(t), Width(w), Height(h)
		{ }
	};

	class IRON_API Window
	{
	public:
		virtual ~Window() { }

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() = 0;
		virtual unsigned int GetHeight() = 0;

		virtual void SetEventCallback(const std::function<void(Event&)> callback) = 0;
		virtual void SetInternalEventCallback(const std::function<void(Event&)> callback) = 0;
		virtual void SetVSync(bool val) = 0;
		virtual GLFWwindow* GetWindowPointer() = 0;
		virtual std::vector<Event*>* GetEvents() = 0;

		static Window* Create(const WindowProps& prop = WindowProps());
	};
}