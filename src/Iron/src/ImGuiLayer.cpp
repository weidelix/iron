#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "ImGuiLayer.h"
#include <imgui_internal.h>
#include "Window.h"
#include "Application.h"

using namespace ImGui;

namespace Iron
{
    ImFont* ImGuiLayer::m_defaultFont;
    ImFont* ImGuiLayer::m_widgetFont;
    ImFont* ImGuiLayer::m_titleBarFont;
    ImFontAtlas* ImGuiLayer::m_fontAtlas;

    ImGuiLayer::ImGuiLayer(const std::string &name)
        :Layer(name)
    {
        m_propStack.reserve(10);
    }
    
    ImGuiLayer::~ImGuiLayer() { }
    
    void ImGuiLayer::OnAttach() 
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        CreateContext(m_fontAtlas);
        ImGuiIO& io = GetIO();
        m_defaultFont  = io.Fonts->AddFontFromFileTTF("../../../res/fonts/Quicksand-Medium.ttf" , 18);
        m_widgetFont   = io.Fonts->AddFontFromFileTTF("../../../res/fonts/Quicksand-Regular.ttf", 15);
        m_titleBarFont = io.Fonts->AddFontFromFileTTF("../../../res/fonts/Quicksand-Bold.ttf"   , 25);
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.Fonts->AddFontDefault(m_defaultFont->ConfigData);

        // Setup Platform/Renderer bindings
        Window &window = Application::Get().GetWindow();
        ImGui_ImplGlfw_InitForOpenGL(window.GetWindowPointer(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
        // Setup Dear ImGui style
        CherryTheme();
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        DestroyContext();
    }
    
    void ImGuiLayer::OnUpdate() 
    { 
        auto& window = Application::Get();
        ImGui_ImplOpenGL3_NewFrame();        
        ImGui_ImplGlfw_NewFrame();
        NewFrame();
            
        float indent_size = 10.0f;
        bool show = true;

        Begin("Sample_1 Test");
        if (CollapsingHeader("Position"))
        {
            float test[4] = {0, 0, 0, 0};
            BeginPropPanel(indent_size);
            BeginPropPanel(indent_size);
            DragFloat4("##0", test, 1.0f, 1.0f);
            TextWrapped("when the days are cold the cars all folded the saints we prayed are all made of gold");
            EndPropPanel();
            DragFloat4("##0", test, 1.0f, 1.0f);
            TextWrapped("we dont believe whats on tv because its what we want to see and what we want we know we cant believe");
            EndPropPanel();
        }
        End();

        Begin("Sample_2 Test");
        if (CollapsingHeader("Hatdog"))
        {
            float test[4] = {0, 0, 0, 0};
            BeginPropPanel(indent_size);
            BeginPropPanel(indent_size); 
            DragFloat4("##0", test, 1.0f, 1.0f);
            TextWrapped("but our house gets cold when cut the heating without you ill be freezing");
            EndPropPanel();
            DragFloat4("##0", test, 1.0f, 1.0f);
            TextWrapped("have you ever loved? We should go again. I'll be down when its over baby yeah! I'll be your man");
            EndPropPanel();
        }        
        End();
        Render();
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
        glViewport(0, 0, window.GetWindow().GetWidth(), window.GetWindow().GetHeight());
    }

    void ImGuiLayer::OnEvent(Event& event) { }

    void ImGuiLayer::CherryTheme()
    {    
        // cherry colors, 3 intensities
        #define HI(v)   ImVec4(0.502f, 0.075f, 0.256f, v)
        #define MED(v)  ImVec4(0.455f, 0.198f, 0.301f, v)
        #define LOW(v)  ImVec4(0.232f, 0.201f, 0.271f, v)
        // backgrounds (@todo: complete with BG_MED, BG_LOW)
        #define BG(v)   ImVec4(0.13f, 0.13f, 0.13f, v)
        #define HOV(v)  ImVec4(0.20f, 0.20f, 0.20f, v)
        #define DEF(v)  ImVec4(0.17f, 0.17f, 0.17f, v)
        #define ACTV(v) ImVec4(0.13f, 0.13f, 0.13f, v)
        // TEXT
        #define TXT(v) ImVec4(0.860f, 0.930f, 0.890f, v)

        auto& style = GetStyle();

        style.Colors[ImGuiCol_Text] = TXT(0.78f);
        style.Colors[ImGuiCol_TextDisabled] = TXT(0.28f);
        style.Colors[ImGuiCol_WindowBg] = BG(1.0f);
        style.Colors[ImGuiCol_PopupBg] = BG(0.9f);
        style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 1.00f, 0.00f);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        style.Colors[ImGuiCol_FrameBg] = DEF(1.0f);
        style.Colors[ImGuiCol_FrameBgHovered] = HOV(1.0f);
        style.Colors[ImGuiCol_FrameBgActive] = MED(1.00f);
        style.Colors[ImGuiCol_TitleBg] = BG(1.0f);
        style.Colors[ImGuiCol_TitleBgActive] = BG(1.0f);
        style.Colors[ImGuiCol_TitleBgCollapsed] = BG(1.0f);

        style.Colors[ImGuiCol_Tab] = BG(1.00f);
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
        style.Colors[ImGuiCol_PlotLines] = TXT(0.63f);
        style.Colors[ImGuiCol_PlotLinesHovered] = MED(1.00f);
        style.Colors[ImGuiCol_PlotHistogram] = TXT(0.63f);
        style.Colors[ImGuiCol_PlotHistogramHovered] = MED(1.00f);
        style.Colors[ImGuiCol_TextSelectedBg] = MED(0.43f);
        style.Colors[ImGuiCol_ModalWindowDarkening] = BG(0.73f);

        style.ChildRounding = 10.0f;
        style.WindowRounding = 0.0f;
        style.FrameRounding = 3.0f;
        style.ItemSpacing = ImVec2(0, 4);
        style.ItemInnerSpacing = ImVec2(5, 1);
        style.TouchExtraPadding = ImVec2(0, 0);
        style.IndentSpacing = 6.0f;
        style.ScrollbarSize = 12.0f;
        style.ScrollbarRounding = 16.0f;
        style.GrabMinSize = 20.0f;
        style.GrabRounding = 2.0f;        
        
        style.WindowTitleAlign.x = 0.02f;
        style.WindowTitleAlign.y = 0.20f;
        style.FrameBorderSize  = 0.0f;
        style.FramePadding     = ImVec2(4.0f, 4.0f);
        style.WindowPadding    = ImVec2(15.0f, 3.0f);
        style.WindowBorderSize = 4.0f;
        style.WindowMinSize    = ImVec2(50, 100);
        style.WindowMenuButtonPosition = ImGuiDir_Right;
    }
    
    void ImGuiLayer::Begin(const char *name, bool* isOpen, ImGuiWindowFlags flags)
    {
        PushFont(m_titleBarFont);
        PushStyleColor(ImGuiCol_Text, ImVec4(0.652f, 0.275f, 0.456f, 1.0f));
        Begin(name, isOpen, flags);
        PopStyleColor();
        PopFont();
        PushFont(m_defaultFont);
    }

    void ImGuiLayer::End()
    {
        PopFont();
        End(); 
    }

    void ImGuiLayer::BeginWidget(ImFont *font)
    {
        PushFont(font);
    }

    void ImGuiLayer::EndWidget()
    {
        PopFont();
    }

    void ImGuiLayer::BeginPropPanel(float indent)
    {
        Dummy({ 0.0f, 0.0f });
        SameLine();
        Indent(indent);
        ImVec2 itemMin = GetItemRectMin(); 
        m_propStack.emplace_back(itemMin.x, itemMin.y, indent);
        PushItemWidth(GetWindowContentRegionWidth() - (indent * (PropStackSize() - 1)) - GetStyle().FramePadding.x);
    }

    void ImGuiLayer::EndPropPanel()
    {
        ImVec2 itemMax = GetItemRectMax();
        ImVec3& data = m_propStack.back();       
        GetWindowDrawList()->AddLine
           ({data.x, data.y},
            {data.x, itemMax.y},
            GetColorU32({ 1.0f - (0.18f * PropStackSize()), 0.275f, 0.456f, 1.0f }),
            2.0f);

        if (PropStackSize() < 0) 
            IRON_CORE_ASSERT(false, "[LAYER ERROR] BeginPropLayer/EndPropLayer mismatch, call BeginPropLayer before calling EndPropLayer");
        PopItemWidth();
        Unindent(data.z);
        m_propStack.pop_back();
    }
}
