#include "Iron.h"
#include <iostream>


class Sandbox : public Iron::Application
{
public:
    Sandbox() { }
    ~Sandbox() { }

    void OnStart() override
    {
        std::cout << "Start" << std::endl;
    }

    void OnUpdate() override
    {
        std::cout << "Update" << std::endl;
    }
};

Iron::Application *Iron::CreateApplication()
{
    return new Sandbox();
}   

