#pragma once
#include "pch.h"
#include "Core.h"
#include "Window.h"
#include "Iron/platform/Windows/WindowsWindow.h"
#include "Input.h"
#include "LayerStack.h"

namespace Iron
{
    class IRON_API Application 
    {
    private:
        std::unique_ptr<Window> m_window;
        bool isRunning = true;
        LayerStack m_layerStack;
        static Application* m_instance;

    public:
        Application();
        virtual ~Application()  { }
        virtual void Start()  { }
        virtual void Update() { }
        virtual void OnEvent(Event& event) { }
        virtual void OnExit() { }
        virtual bool Run();
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