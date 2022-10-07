#pragma once

#include "Renderer/Components/Material.hpp"
#include "pch.hpp"
#include "Core.hpp"
#include "Window.hpp"
#include "Platform/Windows/WindowsWindow.hpp"
#include "Input.hpp"
#include "LayerStack.hpp"

namespace Iron
{
	class IRON_API IronEngine 
	{
	private:
		static IronEngine* m_instance;
		const std::unique_ptr<Window> m_window;
		bool isRunning = true;
		LayerStack m_layerStack;
		Input m_input;
		void EventCallback(Event& event);
	
	public:
		IronEngine();
		virtual ~IronEngine(){ }
		virtual void Start(){ }
		virtual void Update(){ }
		virtual void OnExit(){ }
		virtual bool Run();
		virtual void OnEvent(Event& event) { }
		Input GetInput();
		static IronEngine &Get();
		Window& GetWindow();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		IEShader &LoadShader(const std::string &path);
		IEShader &LoadShader(const std::string &name, const std::string &path);
		IEShader &LoadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
		IEMaterial &CreateMaterial(const std::string &name);
	};

	// Define in client
	extern IronEngine* CreateApplication();
}
