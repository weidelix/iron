#pragma once 

#ifdef IRON_PLATFORM_WINDOW
    
    extern Iron::Application* Iron::CreateApplication();
 
    int main()
    {
        Iron::Log::Init();
        auto* app = Iron::CreateApplication();
        app->Run();
        delete app;
    }

#else
    #error Iron only supports windows at the moment!
#endif