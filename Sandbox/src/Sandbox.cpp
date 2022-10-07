#include "Iron.hpp"
#include "Renderer/Components/Material.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Renderer/GameObject.hpp"
#include "Renderer/RenderCommand.hpp"
#include "Renderer/Renderer.hpp"
#include "Renderer/Texture2D.hpp"
#include "fwd.hpp"
#include <memory>
#include <string>

using namespace Iron;

class Sandbox : public IronEngine
{
public:
	GameObject bag = GameObject::Load(std::string("backpack/backpack.obj"));
	GameObject gun = GameObject::Load(std::string("M4A1/m4a1.obj"));
	
	Sandbox()
	{
		IEMaterial bagMat = CreateMaterial("bag");
		IETexture2D bagAlbedo = CREATE_TEXTURE2D_PATH(TEX_ALBEDO, "backpack/1001_albedo.jpg", false);
		IETexture2D bagAo = CREATE_TEXTURE2D_PATH(TEX_AO, "backpack/1001_AO.jpg", false);
		IETexture2D bagNormal = CREATE_TEXTURE2D_PATH(TEX_NORMAL, "backpack/1001_normal.png", false);
		IETexture2D bagSpecular = CREATE_TEXTURE2D_PATH(TEX_SPECULAR, "backpack/1001_metallic.jpg", false);
		bagMat->SetAlbedo(bagAlbedo);
		bagMat->SetNormal(bagNormal);
		bagMat->SetAO(bagAo);
		bagMat->SetSpecular(bagSpecular);
		bag.SetMaterial(bagMat);
		
		IEMaterial gunMat = CreateMaterial("gun");
		IETexture2D gunAlbedo = CREATE_TEXTURE2D_PATH(TEX_ALBEDO, "M4A1/textures/n4a1_albedo.jpg", false);
		IETexture2D gunAo = CREATE_TEXTURE2D_PATH(TEX_AO, "M4A1/textures/n4a1_AO.jpg", false);
		IETexture2D gunNormal = CREATE_TEXTURE2D_PATH(TEX_NORMAL, "M4A1/textures/n4a1_normal.jpg", false);
		IETexture2D gunSpecular = CREATE_TEXTURE2D_PATH(TEX_SPECULAR, "M4A1/textures/n4a1_metallic.jpg", false);		
		gunMat->SetAlbedo(gunAlbedo);
		gunMat->SetNormal(gunNormal);
		gunMat->SetAO(gunAo);
		gunMat->SetSpecular(gunSpecular);
		gun.SetMaterial(gunMat);
		
		gun.GetTransform().SetScale(Vector3(0.05f));
		gun.GetTransform().SetPosition(Vector3(-3.0f, 0.0f, 0.0f));
		bag.GetTransform().SetPosition(Vector3(3.0f, 0.0f, 0.0f));
	}

	// Runs code on start
	void Start() override 
	{
		
	}

	// Runs code every frame
	void Update() override
	{
		gun.GetTransform().SetRotation(Quaternion::ToQuat(Vector3(0.0f, Time::TimeElapsed() * 0.5f, 0.0f)));
		bag.GetTransform().SetRotation(Quaternion::ToQuat(Vector3(0.0f, Time::TimeElapsed() * 0.5f, 0.0f)));
		
		bag.Draw();
		gun.Draw();
	}

	void OnEvent(Event &e) override
	{

	}
};

Iron::IronEngine* Iron::CreateApplication()
{
	IRON_INFO("Iron Engine v{}", IRON_VERSION);
	return new Sandbox();
}
