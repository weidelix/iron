#include <glad/glad.h>
#include <memory>
#include "Log.hpp"
#include "Renderer/Components/Material.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Renderer/Texture2D.hpp"

namespace Iron
{
	Material::Material()
	{

	}

	Material::~Material()
	{
		m_albedo->RemoveTexture();
		m_ao->RemoveTexture();
		m_normalMap->RemoveTexture();
		m_heightMap->RemoveTexture();
	}

	void Material::SetAlbedo(const std::shared_ptr<Texture2D> &albedo)
	{
		m_albedo = albedo;
	}

	void Material::SetAO(const std::shared_ptr<Texture2D> &ao)
	{
		m_ao = ao;
	}

	void Material::SetTint(float r, float g, float b)
	{
		m_tint.SetX(r);
		m_tint.SetY(g);
		m_tint.SetZ(b);
	}

	void Material::ApplyMaterial(const std::shared_ptr<Shader> &shader)
	{
		shader->SetFloat4("fMaterial.tint", m_tint.GetX(), m_tint.GetY(), m_tint.GetZ(), 1.0f);

		if (m_albedo) 
		{
			glActiveTexture(GL_TEXTURE0);
			m_albedo->Bind();
			shader->SetInt1(("fMaterial." + m_albedo->GetType() + "1").c_str(), 0);
			shader->SetBool("useAlbedo", true);
		}
		else 
		{
			shader->SetBool("useAlbedo", false);
		}
		
		if (m_ao)
		{
			glActiveTexture(GL_TEXTURE0 + 1);
			m_ao->Bind();
			shader->SetInt1(("fMaterial." + m_ao->GetType()).c_str(), 1);
			shader->SetBool("useAO", true);
		}
		else
		{
			shader->SetBool("useAO", false);
		}
	}
}