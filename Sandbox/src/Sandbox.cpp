#include "Iron.hpp"
#include <memory>

using namespace Iron;

class Sandbox : public Application
{
public:
	GameObject bag = GameObject::Load(std::string("backpack/backpack.obj"));
	Vector3 rot = Vector3(0.0f, 0.0f, 0.0f);
	
	// Runs code on start
	void Start() override 
	{

	}

	// Runs code every frame
	void Update() override
	{
		bag.Draw();
	}

	void OnEvent(Event &e) override
	{
		/*const float speed = 3.0f * Time::DeltaTime();
		Transform &transform = bag.GetTransform();
		Vector3 &pos = transform.GetPosition();
    
		if (e.GetEventType() == EventType::KeyPress)
		{
			KeyPressEvent &event = (KeyPressEvent&)e;

			if (event.GetKeyEvent() == Key::W)
				pos = pos + transform.Front() * speed;
			else if (event.GetKeyEvent() == Key::S)
				pos = pos - transform.Front() * speed;
			else if (event.GetKeyEvent() == Key::A)
				pos = pos + transform.Right() * speed;
			else if (event.GetKeyEvent() == Key::D)
				pos = pos - transform.Right() * speed;
			else if (event.GetKeyEvent() == Key::Up)
				pos = pos + transform.Up() * speed;
			else if (event.GetKeyEvent() == Key::Down)
				pos = pos - transform.Up() * speed;
			else if (event.GetKeyEvent() == Key::Left)
				rot.SetY(rot.GetY() + 0.01f);
			else if (event.GetKeyEvent() == Key::Right)
				rot.SetY(rot.GetY() - 0.01f);

			bag.GetTransform().SetRotation(Quaternion::ToQuat(rot));
			transform.SetPosition(pos);
		}*/
	}
};

// Define "Iron::CreateApplication" method that returns an object that inherits from the Application class
Iron::Application* Iron::CreateApplication()
{
	IRON_INFO("Iron Engine v{}", IRON_VERSION);
	return new Sandbox();
}