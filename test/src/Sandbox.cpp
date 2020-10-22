#include "Iron.h"

//NOTE: TRY RECONFIGURING PROJECT THEN REBUILDING WHEN NOT WORKING PROPERLY

class Sandbox : public Iron::Application
{
public:    
    // Runs code on start
    void Start() override
    {

    }

    // Runs code every frame
    void Update() override
    {   
        
    }
 
    void OnEvent(Iron::Event& event) override 
    {
        
    }

    void OnExit() override 
    { 

    }
};

// Define "Iron::CreateApplication" method that returns an object tha    inherits from "Application" class
Iron::Application* Iron::CreateApplication()
{
    LOG_INFO("Iron Engine v{}", IRON_VERSION);
    return new Sandbox();
}