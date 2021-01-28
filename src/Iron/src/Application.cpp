#include "pch.hpp"
#include "Renderer/Renderer.hpp"
#include "Event/Event.hpp"
#include "ImGuiLayer.hpp"
#include "Application.hpp"
#include "Renderer/GameObject.hpp"

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
	
	float pos[] = 
	{
		-1.0f, -1.0f, 0.0f,
  	 1.0f, -1.0f, 0.0f,
  	 0.0f,  1.0f, 0.0f,
	};

	unsigned int indices[] = 
	{
		0, 1, 2,
	};

	bool Application::Run() 
	{
		RenderCommand::UseRenderer(Api::OpenGL);
		RenderCommand::SetClearColor({ 0.2, 0.2, 0.2, 1.0 });
		m_instance->Start();
		
		while(isRunning)
		{
			RenderCommand::Clear();
			m_instance->Update();
			for (auto* layer : m_layerStack)
			{
				layer->OnUpdate(); 
			}
			m_window->OnUpdate();
		}
		return true; 
	}
	
	bool Callback(Event& event)
	{
		IRON_INFO(event.ToString());
		return true;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KeyPressEvent>(std::bind(&Callback, std::placeholders::_1));
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
