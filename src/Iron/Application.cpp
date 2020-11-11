#include "Application.h"
#include "Log.h"
#include "pch.h"
#include "Event/Event.h"
#include "ImGuiLayer.h"

namespace Iron
{
    Application* Application::m_instance = nullptr;

    Application::Application()
        :m_window(std::unique_ptr<Window>(Window::Create())),
         m_input(m_window.get())
    {
        IRON_CORE_ASSERT(!m_instance, "[IRON]: An instance already exist!");
        m_instance = this;
        m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
    }
    
    bool Application::Run() 
    {
        //PushOverlay(new ImGuiLayer("ImGuiLayer"));
        m_instance->Start();
        while(isRunning)
        {
            glClearColor(0.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            m_instance->Update();

            for (auto* layer : m_layerStack)
                layer->OnUpdate();

            m_window->OnUpdate();            
        }
        return true; 
    }
    
    Input Application::Input()
    {
        return m_input;
    }

    Application& Application::Get() 
    {
        return *m_instance;
    }
    
    Window& Application::GetWindow()
    {
        return *m_window;
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
