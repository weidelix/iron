#pragma once

#include "Window.hpp"
#include "Log.hpp"
#include "Event/MouseEvent.hpp"
#include "Event/WindowEvent.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/ApplicationEvent.hpp"

namespace Iron
{
	class IRON_API WindowsWindow : public Window
	{
	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			std::function<void(Event&)> EventCallback;
			std::vector<Event*> Events;
		};
		WindowData m_data;
		GLFWwindow* m_window;

	public:
		WindowsWindow(const WindowProps& prop);
		~WindowsWindow() override;
		
		inline unsigned int GetWidth() override { return m_data.Width; } 
		inline unsigned int GetHeight() override { return m_data.Height; } 
		inline void SetEventCallback(std::function<void(Event&)> callback) override { m_data.EventCallback = callback; }
		inline GLFWwindow* GetWindowPointer() override { return m_window; }
		inline std::vector<Event*>* GetEvents() override { return &m_data.Events; }
		inline void SetVSync(bool val) override;
		inline void OnUpdate() override;
		
		void Init(const WindowProps& prop);
		void Close();
	};
}