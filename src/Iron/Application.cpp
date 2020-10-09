#include "Application.h"
#include "Log.h"
#include "pch.h"
#include "Iron/Event/Event.h"
#include "Iron/Renderer.h"

namespace Iron
{
    Application::Application()  
    {
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        m_window->SetOnExitCallback(std::bind(&Application::OnExit, this));
    }

    bool Application::Run() 
    {
        this->Start();
        while(isRunning)
        {
            glClearColor(0.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            this->Update();
            m_window->OnUpdate();            
        }
        return true; 
    }

    Input Application::Input()
    {
        return Iron::Input(*(WindowsWindow*)m_window.get());
    }
}