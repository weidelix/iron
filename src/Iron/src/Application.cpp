#include "pch.h"
#include "Event/Event.h"
#include "ImGuiLayer.h"
//#include "Renderer/RenderCommand.h"
#include "Application.h"
//#include "Renderer/Renderer.h"

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
	
	float pos[] = {
		0.5f, -0.5f, 0.0f,
   	0.5f, -0.5f, 0.0f,
   	0.0f,  0.5f, 0.0f
	};

	unsigned int indices[] = 
	{
		0, 1, 2,
		//2, 3, 1
	};


	bool Application::Run() 
	{
		// VertexArray vertexArray = VertexArray::Create();
		// IndexBuffer indexBuffer(indices, 6);
		// VertexBuffer vertexBuffer(pos, 9 * sizeof(float));
		// vertexArray.SetIndexBuffer(&indexBuffer);

		//PushOverlay(new ImGuiLayer("ImGuiLayer"));
		//RenderCommand::SetClearColor({ 0.0, 0.0, 1.0, 1.0 });
		m_instance->Start();
		while(isRunning)
		{
			//RenderCommand::Clear();
			//Renderer::Submit(vertexArray);
			glClear(GL_COLOR_BUFFER_BIT);
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
