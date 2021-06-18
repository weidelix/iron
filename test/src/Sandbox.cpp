#include "Iron.hpp"

using namespace Iron;

//NOTE: TRY RECONFIGURING PROJECT THEN REBUILDING WHEN NOT WORKING PROPERLY
class Sandbox : public Application
{
public:
	GameObject plane = GameObject::CreatePrimitive(Primitives::Plane);
	glm::vec3 rot = glm::vec3(0.0f, 0.0f, 0.0f);

	// Runs code on start
	void Start() override 
	{

	}

	// Runs code every frame
	void Update() override
	{
		plane.Draw();
	}

	void OnEvent(Event &e) override
	{
		const float speed = 3.0f * Time::DeltaTime();
		Transform &transform = plane.GetTransform();
		Position &pos = transform.GetPosition();
    
		if (e.GetEventType() == EventType::KeyPress)
		{
			KeyPressEvent &event = (KeyPressEvent&)e;

			if (event.GetKeyEvent() == Key::W)
				pos.SetPosition(pos.GetPosition() + transform.Front() * speed);
			else if (event.GetKeyEvent() == Key::S)
				pos.SetPosition(pos.GetPosition() - transform.Front() * speed);
			else if (event.GetKeyEvent() == Key::A)
				pos.SetPosition(pos.GetPosition() - transform.Right() * speed);
			else if (event.GetKeyEvent() == Key::D)
				pos.SetPosition(pos.GetPosition() + transform.Right() * speed);
			else if (event.GetKeyEvent() == Key::Up)
				pos.SetPosition(pos.GetPosition() + transform.Up() * speed);
			else if (event.GetKeyEvent() == Key::Down)
				pos.SetPosition(pos.GetPosition() - transform.Up() * speed);
			else if (event.GetKeyEvent() == Key::Left)
				rot.x += 0.01f;
			else if (event.GetKeyEvent() == Key::Right)
				rot.x -= 0.01f;

			plane.GetTransform().SetRotation(Quaternion::ToQuat(rot));
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