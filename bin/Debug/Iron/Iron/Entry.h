#pragma once 

#ifdef IRON_PLATFORM_WINDOW
    
    extern Iron::Application* Iron::CreateApplication();

    int main()
    {
        auto* app = Iron::CreateApplication();
        app->Run();
        Iron::Log::Init();
        Iron::Log::GetCoreLogger()->warn("Initialized!");
        delete app;
    }

#else
    #error Iron only supports window at the moment!
#endif