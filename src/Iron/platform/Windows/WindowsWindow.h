#pragma once

#include "Iron/Window.h"
#include "Iron/Log.h"
#include "Iron/Event/MouseEvent.h"
#include "Iron/Event/WindowEvent.h"
#include "Iron/Event/KeyEvent.h"
//#include "Event/ApplicationEvent.h"

namespace Iron
{
    class IRON_API WindowsWindow : public Window
    {
    private:
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            std::function<void(Event&)> EventCallback;
            std::vector<Event*> Events;
        };
        WindowData m_data;
        GLFWwindow* m_window;

    public:
        WindowsWindow(const WindowProps& prop);
        ~WindowsWindow() override;

        inline unsigned int GetWidth() override { return m_data.Width; } 
        inline unsigned int GetHeight() override { return m_data.Height; } 

        inline void SetEventCallback(std::function<void(Event&)> callback) override { m_data.EventCallback = callback; }
        inline GLFWwindow* GetWindowPointer() override { return m_window; }
        inline std::vector<Event*>& GetEvents() { return m_data.Events; }
        inline void SetVSync(bool val) override;
        inline void OnUpdate() override;

        void Init(const WindowProps& prop);
        void Close();
    };
}