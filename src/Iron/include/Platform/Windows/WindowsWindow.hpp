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
			string Title;
			unsigned int Width, Height;
			bool VSync;
			function<void(Event&)> EventCallback;
			vector<Event*> Events;
		};
		WindowData m_data;
		GLFWwindow* m_window;

	public:
		WindowsWindow(const WindowProps& prop);
		~WindowsWindow() override;
		
		inline unsigned int GetWidth() override { return m_data.Width; } 
		inline unsigned int GetHeight() override { return m_data.Height; } 
		inline void SetEventCallback(function<void(Event&)> callback) override { m_data.EventCallback = callback; }
		inline GLFWwindow* GetWindowPointer() override { return m_window; }
		inline vector<Event*>* GetEvents() override { return &m_data.Events; }
		inline void SetVSync(bool val) override;
		inline void OnUpdate() override;
		
		void Init(const WindowProps& prop);
		void Close();
	};
}