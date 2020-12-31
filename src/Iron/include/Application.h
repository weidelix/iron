#pragma once
#include "pch.h"
#include "Core.h"
#include "Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Input.h"
#include "LayerStack.h"

namespace Iron
{
	class IRON_API Application 
	{
	private:
		static Application* m_instance;
		std::unique_ptr<Window> m_window;
		bool isRunning = true;
		LayerStack m_layerStack;
		Input m_input;

	public:
		Application();
		virtual ~Application()  { }
		virtual void Start()  { }
		virtual void Update() { }
		virtual void OnExit() { }
		virtual bool Run();
		virtual void OnEvent(Event& event);
		Input Input();
		static Application &Get();
		Window& GetWindow();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
	};

	// DEFINE IN CLIENT
	extern Application* CreateApplication();
}
