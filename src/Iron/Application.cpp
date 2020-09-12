#include "Application.h"

namespace Iron
{
    Application::Application()   { }
    Application::~Application()  { }
    void Application::OnStart()  { }
    void Application::OnUpdate() { }
    bool Application::Run() 
    { 
        this->OnStart();
        this->OnUpdate();
        return true; 
    }
}