#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "ImGuiLayer.h"
#include <imgui_internal.h>
#include "Window.h"
#include "Application.h"

namespace Iron
{
    ImFont* ImGuiLayer::m_defaultFont;
    ImFont* ImGuiLayer::m_widgetFont;
    ImFont* ImGuiLayer::m_titleBarFont;
    ImGuiIO& ImGuiLayer::m_io = *(ImGuiIO*)0;

    ImGuiLayer::ImGuiLayer(const std::string &name)
        :Layer(name){ }

    ImGuiLayer::~ImGuiLayer() { }

    void ImGuiLayer::OnAttach() 
    { 
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        //m_io = ImGui::GetIO();
        ImGuiIO& io = ImGui::GetIO();
        // Setup Platform/Renderer bindings
        Window &window = Application::Get().GetWindow();
        ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPointer(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        // Setup Dear ImGui style
        CherryTheme();
    }
    void  ImGuiLayer::OnDetach() 
    {
        ImGui_ImplOpenGL3_Shutdown();
	    ImGui_ImplGlfw_Shutdown();
	    ImGui::DestroyContext();
    }
    
    void ImGuiLayer::OnUpdate() 
    { 
        auto& window = Application::Get();
        ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
        
        bool show = true;

        {
            float float3[3] = { 0.0f ,0.0f, 0.0f };
            Begin("Properties");
            BeginWidget();
            if (ImGui::CollapsingHeader("Animation"))
            {   
                float indent_size = 20.0f;
                auto& data_0 = BeginPropPanel(indent_size);
                auto& data_9 = BeginPropPanel(indent_size);
                float float3[3] = { 0.0f ,0.0f, 0.0f };

                BeginWidget(m_widgetFont);
                auto& data_11 = BeginPropPanel(indent_size);
                ImGui::DragFloat3("##hidden DragFloat3_1", float3, 1.0f, 0.0f, 100.0f);
                ImGui::DragFloat3("##hidden DragFloat3_2", float3, 1.0f, 0.0f, 100.0f);
                ImGui::DragFloat3("##hidden DragFloat3_3", float3, 1.0f, 0.0f, 100.0f);
                if (ImGui::CollapsingHeader("Camera"))
                {   
                    auto& data_8 = BeginPropPanel(indent_size);
                    float float3[3] = { 0.0f ,0.0f, 0.0f };
                    BeginWidget(m_widgetFont);
                    ImGui::PushItemWidth(ImGui::GetWindowWidth() - 6.0f);
                    ImGui::DragFloat3("##hidden DragFloat3_1", float3, 1.0f, 0.0f, 100.0f);
                    ImGui::DragFloat3("##hidden DragFloat3_2", float3, 1.0f, 0.0f, 100.0f);
                    ImGui::DragFloat3("##hidden DragFloat3_3", float3, 1.0f, 0.0f, 100.0f);
                    ImGui::Text("Hatdog");
                    EndWidget();
                    ImGui::PopItemWidth();
                    EndPropPanel(data_8);
                }
                EndPropPanel(data_11);
                EndWidget();

                BeginWidget();
                ImGui::TextWrapped("Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog  Hatdog");
                EndWidget();

                EndPropPanel(data_9);
                EndPropPanel(data_0);
            }
            EndWidget();
            End();
        }
        ImGui::Render();
        glViewport(0, 0, window.GetWindow().GetWidth(), window.GetWindow().GetHeight());
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    
    void ImGuiLayer::OnEvent(Event& event) { }

    void ImGuiLayer::CherryTheme()
    {
        //Setup Fonts
        m_defaultFont  = ImGui::GetIO().Fonts->AddFontFromFileTTF("../../../res/fonts/Quicksand-Medium.ttf" , 18);
        m_widgetFont   = ImGui::GetIO().Fonts->AddFontFromFileTTF("../../../res/fonts/Quicksand-Regular.ttf", 15);
        m_titleBarFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("../../../res/fonts/Quicksand-Bold.ttf"   , 25);
        
        //ImGui::GetIO().FontDefault = m_defaultFont;

        // cherry colors, 3 intensities
        #define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
        #define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
        #define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
        // backgrounds (@todo: complete with BG_MED, BG_LOW)
        #define BG(v)   ImVec4(0.13f, 0.13f, 0.13f, v)
        #define HOV(v)  ImVec4(0.20f, 0.20f, 0.20f, v)
        #define DEF(v)  ImVec4(0.17f, 0.17f, 0.17f, v)
        #define ACTV(v) ImVec4(0.13f, 0.13f, 0.13f, v)
        // text
        #define TEXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

        auto& style = ImGui::GetStyle();

        style.Colors[ImGuiCol_Text] = TEXT(0.78f);
        style.Colors[ImGuiCol_TextDisabled] = TEXT(0.28f);
        style.Colors[ImGuiCol_WindowBg] = BG(1.0f); // Darker BG
        style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = DEF(1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = HOV(1.0f);
        style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
        style.Colors[ImGuiCol_TitleBg] = BG(1.0f);
        style.Colors[ImGuiCol_TitleBgActive] = BG(1.0f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = BG(1.0f);

        style.Colors[ImGuiCol_Tab] = BG(1.00f); // E
        style.Colors[ImGuiCol_TabHovered] = MED(0.86f);
        style.Colors[ImGuiCol_TabActive] = HI(1.00f);
        style.Colors[ImGuiCol_TabUnfocused] = LOW(0.60f);
        style.Colors[ImGuiCol_TabUnfocusedActive] = MED(0.60f);
        style.Colors[ImGuiCol_MenuBarBg] = BG(0.47f);
        style.Colors[ImGuiCol_ScrollbarBg] = BG(1.00f);
        style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.09f, 0.15f, 0.16f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered] = MED(0.78f);
        style.Colors[ImGuiCol_ScrollbarGrabActive] = MED(1.00f);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.47f, 0.77f, 0.83f, 0.14f);
        style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.71f, 0.22f, 0.27f, 1.00f);
        style.Colors[ImGuiCol_Button] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.13f, 0.14f, 0.17f, 1.00f);
        style.Colors[ImGuiCol_Header] = DEF(1.0f);
        style.Colors[ImGuiCol_HeaderHovered] = HOV(1.0f);
        style.Colors[ImGuiCol_HeaderActive] = MED(1.0f);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 0.04f);
        style.Colors[ImGuiCol_ResizeGripHovered] = MED(0.78f);
        style.Colors[ImGuiCol_ResizeGripActive] = MED(1.00f);
        style.Colors[ImGuiCol_PlotLines] = TEXT(0.63f);
        style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = TEXT(0.63f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
        style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

        style.ChildRounding = 10.0f;
        style.WindowRounding = 0.0f;
        style.FrameRounding = 3.0f;
        style.ItemSpacing = ImVec2(7, 4);
        style.ItemInnerSpacing = ImVec2(5, 1);
        style.TouchExtraPadding = ImVec2(0, 0);
        style.IndentSpacing = 6.0f;
        style.ScrollbarSize = 12.0f;
        style.ScrollbarRounding = 16.0f;
        style.GrabMinSize = 20.0f;
        style.GrabRounding = 2.0f;        
        
        style.WindowTitleAlign.x = 0.02f;
        style.WindowTitleAlign.y = 0.20f;
        style.FrameBorderSize  = 3.0f;
        style.FramePadding     = ImVec2(0.0f, 2.0f);
        style.WindowPadding    = ImVec2(15.0f, 5.0f);
        style.WindowBorderSize = 1.0f;
        style.WindowMinSize    = ImVec2(50, 100);
        style.WindowMenuButtonPosition = ImGuiDir_Right;
    }
    
    void ImGuiLayer::Begin(const char *name, bool* isOpen, ImGuiWindowFlags flags)
    {
        ImGui::PushFont(m_titleBarFont);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.652f, 0.275f, 0.456f, 1.0f));
        ImGui::Begin(name, isOpen, flags);
        ImGui::PopStyleColor();
        ImGui::PopFont();
    }

    void ImGuiLayer::End()
    {
        ImGui::End(); 
    }

    void ImGuiLayer::BeginWidget(ImFont *font)
    {
        ImGui::PushFont(font);
    }

    void ImGuiLayer::EndWidget()
    {
        ImGui::PopFont();
    }

    ImVec4 ImGuiLayer::BeginPropPanel(float w)
    {
        m_propStack++;
        ImGui::Dummy({0.0f, 0.0f});
        ImGui::SameLine();
        ImGui::Indent(w);
        ImVec2 itemMin = ImGui::GetItemRectMin(); 
        return ImVec4(itemMin.x, itemMin.y, w, NULL);  
    }

    void ImGuiLayer::EndPropPanel(ImVec4& data)
    {
        ImVec2 itemMax = ImGui::GetItemRectMax();        
        ImGui::GetWindowDrawList()->AddLine
           ({data.x, data.y},
            {data.x, itemMax.y},
            ImGui::GetColorU32(ImVec4(1.0 - (0.18 * (float)m_propStack), 0.275f, 0.456f, 1.0f)),
            2.0f);

        m_propStack--;
        if (m_propStack < 0) IRON_CORE_ASSERT(false, "IMGUI LAYER ERROR", "BeginPropLayer/EndPropLayer mismatch, call BeginPropLayer before calling EndPropLayer\n");
        ImGui::Unindent(data.z);
    }
}