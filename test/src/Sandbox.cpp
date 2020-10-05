#include "Iron.h"

//NOTE: TRY RECONFIGURING PROJECT THEN REBUILDING WHEN NOT WORKING PROPERLY
class Sandbox : public Iron::Application
{
public:
    //* Runs code on start
    void OnStart() override
    {
        
    }

    //* Run code every frame
    void OnUpdate() override
    {
        
    }

    void OnEvent(Iron::Event& event) override { }

    void OnExit() override { }
};

//* Define "Iron::CreateApplication" method that returns an object that inherits from "Application" class
Iron::Application* Iron::CreateApplication()
{
    LOG_INFO("Iron Engine v{0}", IRON_VERSION);
    return new Sandbox();
}