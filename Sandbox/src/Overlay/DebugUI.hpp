// #pragma once

// #include "ImGui/ImGui_GLFW.h"
// #include "ImGui/ImGui_OpenGL3.h"
// #include "Event/MouseEvent.hpp"
// #include "IronEngine.hpp"

// class DebugUI : public Iron::Layer
// {
// private:
// 	Iron::IronEngine &m_engine;

// public: 
// 	DebugUI(const std::string& name, Iron::IronEngine &engine);
// 	~DebugUI();

// 	void OnAttach() override;
// 	void OnDetach() override;
// 	void OnUpdate() override;
// 	void OnEvent(Iron::Event& event) override;
// 	bool HandleKeyPress(Iron::MouseButtonPressedEvent& event);
// };