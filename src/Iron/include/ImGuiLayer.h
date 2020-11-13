#pragma once

#include "Platform/OpenGL/ImGui_GLFW.h"
#include "Platform/OpenGL/ImGui_OpenGL3.h"
#include "Log.h"
#include "Core.h"
#include "Layer.h"

namespace Iron
{
    class ImGuiLayer : public Layer 
    {
    private:
        struct ImVec3
        {
            float x, y, z;
            ImVec3()                                { x = y = z = 0.0f; }
            ImVec3(float _x, float _y, float _z)    { x = _x; y = _y; z = _z; }
        };
        
        static ImFont* m_titleBarFont;
        static ImFont* m_defaultFont;
        static ImFont* m_widgetFont;
        static ImFontAtlas* m_fontAtlas;
        std::vector<ImVec3> m_propStack;
        

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
        inline void BeginWidget(ImFont* font = m_defaultFont);
        inline void End();
        inline void BeginPropPanel(float indent = 0.0f);
        inline void EndPropPanel(); 
        inline int  PropStackSize() { return static_cast<int>(m_propStack.size()); }
        inline void EndWidget();
    };
}