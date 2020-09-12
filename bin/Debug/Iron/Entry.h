#pragma once 

#ifdef IRON_PLATFORM_WINDOW
    
    extern Iron::Application* Iron::CreateApplication();

    int main()
    {
        auto* app = Iron::CreateApplication();
        app->Run();
        delete app;
    }

#else
    #error Iron only supports window at the moment!
#endif