#include <glad/glad.h>
#include "WindowsWindow.h"

namespace Iron
{
    static bool s_glfwIsInitialized = false;

    Window* Window::Create(const WindowProps& prop)
    {
        return new WindowsWindow(prop);
    }

    WindowsWindow::WindowsWindow(const WindowProps& prop)
    {
        Init(prop);
    }

    WindowsWindow::~WindowsWindow()
    {
        Close();
    }
    
    void WindowsWindow::Init(const WindowProps& prop)
    {
        m_data.Title  = prop.Title;
        m_data.Width  = prop.Width;
        m_data.Height = prop.Height;

        if (!s_glfwIsInitialized)
        {
            int glfwState = glfwInit();
            IRON_CORE_ASSERT(glfwState, "Failed to initialize glfw");
            s_glfwIsInitialized = true;
        }
    
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        m_window = glfwCreateWindow((int)m_data.Width, (int)m_data.Height, m_data.Title.c_str(), nullptr, nullptr);
        
        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, &m_data);
        glfwSwapInterval(1);
        
        int gladState = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        IRON_CORE_ASSERT(gladState, "failed to initialize glad");

        glfwSetErrorCallback([](int error, const char* desc)
        {
            IRON_CORE_ERROR("[GLFW ERROR]({0}): {1}", error, desc);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            glfwDestroyWindow(window);
        });

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width; 
            data.Height = height; 
            WindowResizeEvent e(width, height);
            data.EventCallback(e);
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mod)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action)
            {
            case GLFW_PRESS: 
            {
                MouseButtonPressedEvent* e = new MouseButtonPressedEvent(button);
                data.EventCallback(*e);
                data.Events.push_back(e);
            }
            break;
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent* e = new MouseButtonReleasedEvent(button);
                data.EventCallback(*e);
                data.Events.push_back(e);
            } 
            break;
            }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int key)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyPressEvent* e = new KeyPressEvent(key, false);
            data.EventCallback(*e);
            data.Events.push_back(e);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            switch(action)
            {
                case GLFW_PRESS:
                {
                    if (mods != 0)
                    {
                        KeyCombinationEvent* e = new KeyCombinationEvent(key, mods);
                        data.EventCallback(*e);
                        data.Events.push_back(e);
                    }

                    if (mods == 0 && key > 122 && key < 320 || key > 339 && key < 349)
                    {
                        KeyPressEvent* e = new KeyPressEvent(key, false);
                        data.EventCallback(*e);
                        data.Events.push_back(e);
                    }
                }
                break;

                case GLFW_RELEASE:
                {
                    KeyReleaseEvent* e = new KeyReleaseEvent(key);
                    data.EventCallback(*e);
                    data.Events.push_back(e);
                }
                break;

                case GLFW_REPEAT:
                {
                    if  (mods != 0)
                    {
                        KeyCombinationEvent* e = new KeyCombinationEvent(key, mods);               
                        data.EventCallback(*e);
                        data.Events.push_back(e);
                    }

                    if (mods == 0 && key > 122 && key < 320 || key > 339 && key < 349)
                    {
                        KeyPressEvent* e = new KeyPressEvent(key, true);
                        data.EventCallback(*e);
                        data.Events.push_back(e);
                    }
                }
                break;
            }
        });
    }

    void WindowsWindow::Close()
    {
        glfwTerminate();
    }

    void WindowsWindow::OnUpdate()
    {
        for (auto* e : m_data.Events)
            delete e;
        m_data.Events.clear();
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void WindowsWindow::SetVSync(bool val)
    {
        if (val)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        m_data.VSync = true;
    }
}