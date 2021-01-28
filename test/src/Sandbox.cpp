#include "Iron.hpp"

using namespace Iron;

//NOTE: TRY RECONFIGURING PROJECT THEN REBUILDING WHEN NOT WORKING PROPERLY
class Sandbox : public Application
{
public:
	GameObject plane = GameObject::CreatePrimitive(Primitives::Plane);
	
	// Runs code on start
	void Start() override 
	{
		//plane = GameObject::CreatePrimitive(Primitives::Plane);
	}

	// Runs code every frame
	void Update() override
	{
		plane.Draw();
	}
};

// Define "Iron::CreateApplication" method that returns an object that inherits from an "Application" class
Iron::Application* Iron::CreateApplication()
{
   IRON_INFO("Iron Engine v{}", IRON_VERSION);
   return new Sandbox();
}