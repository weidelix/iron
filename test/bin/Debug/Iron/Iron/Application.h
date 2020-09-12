#pragma once 
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #include <imgui_impl_opengl3.h>
// #include <imgui_impl_glfw.h>
#include <iostream>

#include "Core.h"

namespace Iron
{
    class IRON_API Application 
    {
    public:
        Application();
        virtual ~Application();
        virtual void OnStart();
        virtual void OnUpdate();
        bool Run();
    };

    // DEFINE IN CLIENT
    Application* CreateApplication();
}