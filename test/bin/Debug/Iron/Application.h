#pragma once 
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
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
        virtual ~Application();
        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnEvent(Event& event); 
        virtual void OnExit();
        bool Run();
        Input Input();        
    };

    // DEFINE IN CLIENT
    Application* CreateApplication();
}