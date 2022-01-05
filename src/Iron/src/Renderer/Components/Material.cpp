#include <glad/glad.h>
#include <memory>
#include "Renderer/Components/Material.hpp"

namespace Iron
{
	Material::Material()
		: m_tint(1.0f), m_tintA(0.0f)
	{
		// if(mesh->mMaterialIndex >= 0)
    // {
    //   aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			
		// 	std::vector<Texture2D> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		// 	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			
		// 	std::vector<Texture2D> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		// 	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // }
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

	void Material::SetTint(float r, float g, float b, float a)
	{
		m_tint.SetX(r);
		m_tint.SetY(g);
		m_tint.SetZ(b);
		m_tintA = a;
	}

	void Material::ApplyMaterial(const std::shared_ptr<Shader> &shader)
	{
		shader->SetFloat4("fMaterial.tint", m_tint.GetX(), m_tint.GetY(), m_tint.GetZ(), m_tintA);
		
		unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
		
		// for (unsigned int i = 0; i < m_textures.size(); i++)
    // {
			glActiveTexture(GL_TEXTURE0 + 0);
			std::string number;
			std::string name = m_albedo->GetType();

			if(name == "texture_diffuse")
			    number = std::to_string(1);
			// else if(name == "texture_specular")
			//     number = std::to_string(specularNr++);

			m_albedo->Bind();
			shader->SetInt1(("fMaterial." + name + number).c_str(), 0);

			
			glActiveTexture(GL_TEXTURE0 + 1);
			m_ao->Bind();
			shader->SetInt1(("fMaterial." + m_ao->GetType()).c_str(), 1);

		// }
		GlCall(glActiveTexture(GL_TEXTURE0));
	}
}