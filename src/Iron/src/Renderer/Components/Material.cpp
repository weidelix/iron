#include <glad/glad.h>
#include <memory>
#include "Core.hpp"
#include "Log.hpp"
#include "Renderer/Components/Material.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Renderer/Texture2D.hpp"

namespace Iron
{
	Material::Material(const std::string &name)
		: m_name(name),
			m_albedo(std::make_shared<Texture2D>(TEX_ALBEDO, Vector3(1.0f)))
	{

	}

	Material::~Material()
	{
		if (m_albedo) 	m_albedo->RemoveTexture();
		if (m_ao) 			m_ao->RemoveTexture();
		if (m_specular) m_specular->RemoveTexture();
		if (m_normal) 	m_normal->RemoveTexture();
		if (m_height) 	m_height->RemoveTexture();
	}

	void Material::SetAlbedo(const std::shared_ptr<Texture2D> &albedo)
	{
		m_albedo = albedo;
	}

	void Material::SetAO(const std::shared_ptr<Texture2D> &ao)
	{
		m_ao = ao;
	}

	void Material::SetNormal(const std::shared_ptr<Texture2D> &normal)
	{
		m_normal = normal;
	}

	void Material::SetSpecular(const std::shared_ptr<Texture2D> &specular)
	{
		m_specular = specular;
	}

	void Material::SetTint(float r, float g, float b)
	{
		m_tint.SetX(r);
		m_tint.SetY(g);
		m_tint.SetZ(b);
	}

	void Material::ApplyMaterial(const std::shared_ptr<Shader> &shader)
	{
		shader->SetFloat4("material.tint", m_tint.GetX(), m_tint.GetY(), m_tint.GetZ(), 1.0f);

		for (int i = 0; i < 4; ++i) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		if (m_albedo) 
		{
			IRON_CORE_ASSERT(m_albedo->GetType().c_str() == TEX_ALBEDO, "Type Mismatch: Make sure you're using TEX_ALBEDO for diffuse maps!");
			glActiveTexture(GL_TEXTURE0);
			m_albedo->Bind();
			shader->SetInt1(("material." + m_albedo->GetType()).c_str(), 0);
			shader->SetBool("useAlbedo", true);
		}
		else 
		{
			shader->SetBool("useAlbedo", false);
		}
		
		if (m_ao)
		{
			IRON_CORE_ASSERT(m_ao->GetType().c_str() == TEX_AO, "Type Mismatch: Make sure you're using TEX_AO for ambient occlusion maps!");
			glActiveTexture(GL_TEXTURE0 + 1);
			m_ao->Bind();
			shader->SetInt1(("material." + m_ao->GetType()).c_str(), 1);
			shader->SetBool("useAO", true);
		}
		else
		{
			shader->SetBool("useAO", false);
		}

		if (m_normal)
		{
			IRON_CORE_ASSERT(m_normal->GetType().c_str() == TEX_NORMAL, "Type Mismatch: Make sure you're using TEX_NORMAL for normal maps!");
			glActiveTexture(GL_TEXTURE0 + 2);
			m_normal->Bind();
			shader->SetInt1(("material." + m_normal->GetType()).c_str(), 2);
			shader->SetBool("useNormal", true);
		}
		else 
		{
			shader->SetBool("useNormal", false);
		}

		if (m_specular)
		{
			IRON_CORE_ASSERT(m_specular->GetType().c_str() == TEX_SPECULAR, "Type Mismatch: Make sure you're using TEX_SPECULAR for specular maps!");
			glActiveTexture(GL_TEXTURE0 + 3);
			m_specular->Bind();
			shader->SetInt1(("material." + m_specular->GetType()).c_str(), 3);
			shader->SetBool("useSpecular", true);
		}
		else 
		{
			shader->SetBool("useSpecular", false);
		}
	}

	const std::string &Material::GetName()
	{
		return m_name;
	}

	void MaterialLibrary::Add(const IEMaterial &material)
	{
		const std::string& materialName = material->GetName();
		IRON_CORE_ASSERT(m_materialLib.find(materialName) == m_materialLib.end(), "This shader already exist");
		m_materialLib[materialName] = material;
	}
	
	IEMaterial &MaterialLibrary::Get(const std::string &name)
	{
		IRON_CORE_ASSERT(Exists(name), "Material does not exist");
		return m_materialLib[name];
	}

	bool MaterialLibrary::Exists(const std::string &name)
	{
		return m_materialLib.find(name) != m_materialLib.end();
	}
}