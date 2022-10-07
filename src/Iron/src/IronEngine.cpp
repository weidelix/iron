#include "Renderer/Components/Material.hpp"
#include "Renderer/RenderCommand.hpp"
#include "pch.hpp"
#include "Renderer/Renderer.hpp"
#include "Event/Event.hpp"
#include "ImGuiLayer.hpp"
#include "IronEngine.hpp"
#include "Renderer/GameObject.hpp"
#include "Renderer/Shader.hpp"
#include "Internal.hpp"
#include "Log.hpp"
#include "Viewport.hpp"
#include <memory>

namespace Iron
{
	IronEngine* IronEngine::m_instance = nullptr;
	
	IronEngine::IronEngine()
		: m_window(std::unique_ptr<Window>(Window::Create())),
		  m_input(m_window.get())
	{
		IRON_CORE_ASSERT(!m_instance, "[IRON]: An instance already exist!");
		m_instance = this;
		m_window->SetEventCallback(std::bind(&IronEngine::EventCallback, this, std::placeholders::_1));
		m_window->SetInternalEventCallback(std::bind(&Internal::InternalEventsHandler, std::placeholders::_1));
		
		// Load a default shader on start
		Renderer::LoadShader(std::string("default"), 
												 std::string("./../../../res/shaders/default/default.vert"), 
												 std::string("./../../../res/shaders/default/default.frag"));
		Renderer::CreateMaterial("default");
	}

	bool IronEngine::Run() 
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
	void IronEngine::EventCallback(Event& event)
	{
		OnEvent(event);
		for(auto *layer : m_layerStack)
		{
			layer->OnEvent(event);
		}
	}

	Input IronEngine::GetInput()
	{
		return m_input;
	}

	IronEngine& IronEngine::Get() 
	{
		return *m_instance;
	}
	
	Window& IronEngine::GetWindow()
	{
		return *m_window;
	}

	void IronEngine::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void IronEngine::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
	}

	void IronEngine::PopLayer(Layer* layer)
	{
		m_layerStack.PopLayer(layer);
	}

	void IronEngine::PopOverlay(Layer* overlay)
	{
		m_layerStack.PopOverlay(overlay);
	}

	IEShader &IronEngine::LoadShader(const std::string &path)
	{
		return Renderer::LoadShader(path);
	}

	IEShader &IronEngine::LoadShader(const std::string &name, const std::string &path)
	{
		return Renderer::LoadShader(name, path);
	}

	IEShader &IronEngine::LoadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
	{
		return Renderer::LoadShader(name, vertexShaderPath, fragmentShaderPath);
	}

	IEMaterial &IronEngine::CreateMaterial(const std::string &name)
	{
		return Renderer::CreateMaterial(name);
	}
}
