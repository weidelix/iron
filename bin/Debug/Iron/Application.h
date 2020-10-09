#pragma once
// #include <imgui_impl_opengl3.h>
// #include <imgui_impl_glfw.h>
#include "pch.h"
#include "Core.h"
#include "Window.h"
#include "Iron/platform/Windows/WindowsWindow.h"
#include "Input.h"

namespace Iron
{
    class IRON_API Application 
    {
    private:
        std::unique_ptr<Window> m_window;
        bool isRunning = true;

    public:
        Application();
        virtual ~Application()  { }
        virtual void Start()  { }
        virtual void Update() { }
        virtual void OnEvent(Event& event) { }
        virtual void OnExit() { }
        virtual bool Run();
        Input Input();
    };

    // DEFINE IN CLIENT
    Application* CreateApplication();
}