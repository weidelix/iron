#include "Renderer/RenderCommand.hpp"
#include "pch.hpp"
#include "Renderer/Renderer.hpp"
#include "Event/Event.hpp"
#include "ImGuiLayer.hpp"
#include "Application.hpp"
#include "Renderer/GameObject.hpp"
#include "Renderer/Shader.hpp"
#include "Internal.hpp"
#include "Log.hpp"
#include "Viewport.hpp"

namespace Iron
{
	Application* Application::m_instance = nullptr;
	
	Application::Application()
		: m_window(std::unique_ptr<Window>(Window::Create())),
		  m_input(m_window.get())
	{
		IRON_CORE_ASSERT(!m_instance, "[IRON]: An instance already exist!");
		m_instance = this;
		m_window->SetEventCallback(std::bind(&Application::EventCallback, this, std::placeholders::_1));
		m_window->SetInternalEventCallback(std::bind(&Internal::InternalEventsHandler, std::placeholders::_1));
		
		// Load a default shader on start
		Renderer::LoadShader(std::string("default"), std::string("./../../../res/shaders/default.glsl"));
	}

	bool Application::Run() 
	{
		RenderCommand::SetClearColor({ 0.8f, 0.8f, 1.0f, 1.0f });
		Viewport *viewport = new Viewport("Viewport");

		m_layerStack.PushLayer(viewport);
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

			Time::SetDeltaTime();
		}
		return true; 
	}

	// TODO : Change function name to a better one
	void Application::EventCallback(Event& event)
	{
		OnEvent(event);
		for(auto *layer : m_layerStack)
		{
			layer->OnEvent(event);
		}
	}

	Input Application::GetInput()
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
