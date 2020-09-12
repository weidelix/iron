#include <iostream>
#include "Iron.h"

//* NOTE:
//* TRY REBUILDING IRON WHEN SANDBOX IS NOT WORKING
//* IGNORE ERROR LINES INTELLISENSE IS STUPID

class Sandbox : public Iron::Application
{
public:
    // Runs code on start
    void OnStart() override
    {
        DEBUG_INFO("Start");
    }

    // Run code every frame
    void OnUpdate() override
    {
        DEBUG_INFO("Update");
    }
};

Iron::Application *Iron::CreateApplication()
{
    DEBUG_INFO("Iron Engine version {0}", IRON_VERSION);
    return new Sandbox();
}   

