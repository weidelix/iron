#include "Iron.h"

using namespace Iron;

//NOTE: TRY RECONFIGURING PROJECT THEN REBUILDING WHEN NOT WORKING PROPERLY
class Sandbox : public Application
{
public:
    // Runs code on start
    void Start() override
    {
        
    }

    // Runs code every frame
    void Update() override
    {
        //IRON_INFO(Input().Key());
    }
 
    void OnEvent(Event& event) override 
    {

    }
};

// Define "Iron::CreateApplication" method that returns an object that inherits from an "Application" class
Iron::Application* Iron::CreateApplication()
{
    IRON_INFO("Iron Engine v{}", IRON_VERSION);
    return new Sandbox();
}
