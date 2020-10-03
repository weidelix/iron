#include "Application.h"
#include "Log.h"
#include "pch.h"
#include "Iron/Event/Event.h"

namespace Iron
{
    Application::Application()  
    {
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        m_window->SetOnExitCallback(std::bind(&Application::OnExit, this));
    }

    Application::~Application()  { }
    void Application::OnStart()  { }
    void Application::OnUpdate() { }

    void Application::OnEvent(Event& event) { } 
    void Application::OnExit() { } 

    bool Application::Run() 
    {
        this->OnStart();
        while(isRunning)
        {
            this->OnUpdate();
            m_window->OnUpdate();            
        }
        return true; 
    }

    Input Application::Input()
    {
        return Iron::Input(*(WindowsWindow*)m_window.get());
    }
}