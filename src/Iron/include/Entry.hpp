#pragma once 

#if defined(IRON_PLATFORM_WINDOW)
	extern Iron::Application* Iron::CreateApplication();
 
	int main()
	{
		Iron::Log::Init();
		auto* app = Iron::CreateApplication();
		app->Run();
		delete app;
	}
#elif defined(IRON_PLATFORM_LINUX)
	extern Iron::Application* Iron::CreateApplication();
 
	int main()
	{
		Iron::Log::Init();
		auto* app = Iron::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error Iron only supports Windows and Ubuntu based distributions at the moment!
#endif