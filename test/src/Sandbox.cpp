#include "Iron.hpp"

using namespace Iron;

//NOTE: TRY RECONFIGURING PROJECT THEN REBUILDING WHEN NOT WORKING PROPERLY
class Sandbox : public Application
{
public:
	GameObject plane1 = GameObject::CreatePrimitive(Primitives::Plane);
	GameObject plane2 = GameObject::CreatePrimitive(Primitives::Plane);

	Rotation rot1 = Rotation({ 0.01f, 0.02f, 0.01f });
	Rotation rot2 = Rotation({ 0.03f, 0.03f, 0.03f });
	// Runs code on start
	void Start() override 
	{
		// plane1.GetTransform().SetPosition({1.0, 1.0, 1.0});
	}

	// Runs code every frame
	void Update() override
	{
		// plane1.GetTransform().SetRotation(rot1);
		plane1.Draw();
		// plane2.GetTransform().SetRotation(rot2);
		// plane2.Draw();
	}

	void OnEvent(Event &e) override
	{
		const float speed = 3.0f * Time::DeltaTime();
		Transform &transform = plane1.GetTransform();
		Position &pos = transform.GetPosition();
    
		if (e.GetEventType() == EventType::KeyPress)
		{
			KeyPressEvent &event = (KeyPressEvent&)e;

			if (event.GetKeyEvent() == Key::W)
				pos.MoveByZ(speed);
			else if (event.GetKeyEvent() == Key::S)
				pos.MoveByZ(-speed);
			else if (event.GetKeyEvent() == Key::A)
				pos.MoveByX(-speed);
			else if (event.GetKeyEvent() == Key::D)
				pos.MoveByX(speed);
			else if (event.GetKeyEvent() == Key::Up)
				pos.MoveByY(speed);
			else if (event.GetKeyEvent() == Key::Down)
				pos.MoveByY(-speed);

			transform.SetPosition(pos);
		}
	}
};

// Define "Iron::CreateApplication" method that returns an object that inherits from an "Application" class
Iron::Application* Iron::CreateApplication()
{
	IRON_INFO("Iron Engine v{}", IRON_VERSION);
	return new Sandbox();
}