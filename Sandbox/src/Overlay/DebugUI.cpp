// #include <functional>
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <glm.hpp>
// #include "Event/Event.hpp"
// #include "Event/KeyEvent.hpp"
// #include <imgui_internal.h>
// #include "Event/MouseEvent.hpp"
// #include "Log.hpp"
// #include "Window.hpp"
// #include "IronEngine.hpp"
// #include "DebugUI.hpp"
// #include "imgui.h"

// using namespace ImGui;

// DebugUI::DebugUI(const std::string &name, Iron::IronEngine &engine)
// 	:Iron::Layer(name), m_engine(engine)
// {

// }

// DebugUI::~DebugUI() { }

// void DebugUI::OnAttach()
// {
// 	// Setup Dear ImGui context
// 	IMGUI_CHECKVERSION();
// 	CreateContext();
// 	ImGuiIO& io = GetIO();

// 	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
// 	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
// 	io.ConfigWindowsMoveFromTitleBarOnly = true;

// 	// Setup Platform/Renderer bindings
// 	Iron::Window &window = m_engine.GetWindow();
// 	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPointer(), true);
// 	ImGui_ImplOpenGL3_Init("#version 330");
// }

// void DebugUI::OnDetach()
// {
// 	ImGui_ImplOpenGL3_Shutdown();
// 	ImGui_ImplGlfw_Shutdown();
// 	DestroyContext();
// }

// void DebugUI::OnUpdate() 
// { 
// 	auto& win = m_engine.Get().GetWindow();
// 	float indent_size = 10.0f;
// 	bool show = true;
	
// 	ImGui_ImplOpenGL3_NewFrame();        
// 	ImGui_ImplGlfw_NewFrame();
// 	NewFrame();	

// 	ImGuiViewport* viewport = ImGui::GetMainViewport();
// 	ImGui::SetNextWindowPos(viewport->Pos);
// 	ImGui::SetNextWindowSize(viewport->Size);
// 	ImGui::SetNextWindowViewport(viewport->ID);
// 	ImGui::SetNextWindowBgAlpha(0.0f);

// 	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
// 	window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
// 	window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

// 	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
// 	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
// 	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
// 	ImGui::Begin("DockSpace Demo", &show, window_flags);
// 	ImGui::PopStyleVar(3);

// 	ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
// 	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
// 	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
// 	ImGui::End();
	
// 	ImGui::Begin("Properties");
// 	float test[3] = {0, 0, 0};
// 	DragFloat3("fdasfa", test, 1.0f, 1.0f);
// 	ImGui::End();

// 	Render();
// 	ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
// 	glViewport(0, 0, win.GetWidth(), win.GetHeight());
// }

// void DebugUI::OnEvent(Iron::Event& event) 
// {
// 	Iron::EventDispatcher dispatcher(event);
// 	dispatcher.Dispatch<Iron::MouseButtonPressedEvent>(bind(&DebugUI::HandleKeyPress, this, std::placeholders::_1));
// }

// bool DebugUI::HandleKeyPress(Iron::MouseButtonPressedEvent &event)
// {
// 	if (ImGui::GetIO().WantCaptureMouse && event.GetMouseEvent() == Mouse::Mouse_Left)
// 		return true;
// 	else
// 		return false;
// }