#include "Iron.h"

//NOTE: TRY RECONFIGURING PROJECT THEN REBUILDING WHEN NOT WORKING PROPERLY

#define PRINTL(x) std::cout << x << std::endl
#define PRINT(x) std::cout << x

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
    LOG_INFO("Iron Engine v{:.1}\n", IRON_VERSION);
    return new Sandbox();
}