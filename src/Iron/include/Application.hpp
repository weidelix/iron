#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Window.hpp"
#include "Platform/Windows/WindowsWindow.hpp"
#include "Input.hpp"
#include "LayerStack.hpp"

namespace Iron
{
	class IRON_API Application 
	{
	private:
		static Application* m_instance;
		const std::unique_ptr<Window> m_window;
		bool isRunning = true;
		LayerStack m_layerStack;
		Input m_input;
		void EventCallback(Event& event);
	
	public:
		Application();
		virtual ~Application(){ }
		virtual void Start(){ }
		virtual void Update(){ }
		virtual void OnExit(){ }
		virtual bool Run();
		virtual void OnEvent(Event& event) { }
		Input GetInput();
		static Application &Get();
		Window& GetWindow();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
	};

	// Define in client
	extern Application* CreateApplication();
}
