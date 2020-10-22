#pragma once

#include "Platform/OpenGL/imgui_impl_glfw.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"
#include "Core.h"
#include "Layer.h"

namespace Iron
{
    class IRON_API ImGuiLayer : public Layer
    {
    private:
        static ImFont* m_titleBarFont;
        static ImFont* m_defaultFont;
        static ImFont* m_widgetFont;
        static ImFontAtlas* m_fontAtlas;
        int m_propStack = 0;

    public:
        ImGuiLayer(const std::string& name);
        ~ImGuiLayer();
        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event& event) override;
        void CherryTheme();

        // Widgets
        
        inline void Begin(const char *name, bool *isOpen = (bool*)0, ImGuiWindowFlags flags = 0);
        inline void End();
        inline void BeginWidget(ImFont* font = m_defaultFont);
        inline ImVec4 BeginPropPanel(float w = 0.0f);
        inline void EndPropPanel(ImVec4& data);
        inline void EndWidget();
    };
}