#include "Application.h"
#include "Log.h"
#include "pch.h"
#include "Iron/Event/Event.h"
#include "ImGuiLayer.h"

namespace Iron
{
    Application* Application::m_instance = nullptr;

    Application::Application()  
    {
        IRON_CORE_ASSERT(!m_instance, "[GLFW]: Applicaton instance already exist");
        
        m_instance = this;
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }

    bool Application::Run() 
    {
        this->Start();
        PushOverlay(new ImGuiLayer("ImGui Layer"));
        while(isRunning)
        {
            glClearColor(0.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            this->Update();

            for (auto* layer : m_layerStack)
            {
                layer->OnUpdate();
            }

            m_window->OnUpdate();            
        }
        return true; 
    }

    Application& Application::Get() 
    {
        return *m_instance;
    }
    
    Window& Application::GetWindow()
    {
        return *m_window;
    }

    Input Application::Input()
    {
        return Iron::Input(*(WindowsWindow*)m_window.get());
    }

    void Application::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
    }

	void Application::PushOverlay(Layer* overlay)
    {
        m_layerStack.PushOverlay(overlay);
    }

	void Application::PopLayer(Layer* layer)
    {
        m_layerStack.PopLayer(layer);
    }

	void Application::PopOverlay(Layer* overlay)
    {
        m_layerStack.PopOverlay(overlay);
    }
}