#include "Iron.hpp"
#include "Renderer/Components/Material.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Renderer/RenderCommand.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Texture2D.hpp"
#include "fwd.hpp"
#include <memory>

using namespace Iron;

class Sandbox : public Application
{
public:
	GameObject gun = GameObject::Load(std::string("M4A1/m4a1.obj"));
	
	Sandbox()
	{
		std::shared_ptr<Texture2D> albedo = std::make_shared<Texture2D>(TEX_ALBEDO, "M4A1/textures/n4a1_albedo.jpg", false);
		std::shared_ptr<Texture2D> ao = std::make_shared<Texture2D>(TEX_AO, "M4A1/textures/n4a1_AO.jpg", false);

		// gun.SetAlbedo(albedo);
		// gun.SetAO(ao);
		gun.GetMaterial()->SetAO(ao);
		gun.GetTransform().SetScale(Vector3(0.05f));
	}

	// Runs code on start
	void Start() override 
	{

	}

	// Runs code every frame
	void Update() override
	{
		gun.Draw();
	}

	void OnEvent(Event &e) override
	{

	}
};

// Define "Iron::CreateApplication" method that returns an object that inherits from the Application class
Iron::Application* Iron::CreateApplication()
{
	IRON_INFO("Iron Engine v{}", IRON_VERSION);
	return new Sandbox();
}