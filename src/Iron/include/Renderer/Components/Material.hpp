#pragma once

#include "Core.hpp"
#include "Renderer/Components/Material.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Renderer/Texture2D.hpp"
#include "Renderer/Shader.hpp"
#include "assimp/material.h"
#include "pch.hpp"
#include <memory>

#define TEX_AO std::string("texture_ao")
#define TEX_ALBEDO std::string("texture_diffuse1")
#define TEX_ALBEDO2 std::string("texture_diffuse2")
#define TEX_NORMAL std::string("texture_normal")
#define TEX_HEIGHT std::string("texture_height")
#define TEX_SPECULAR std::string("texture_specular1")
#define TEX_SPECULAR2 std::string("texture_specular2")

#define CREATE_MATERIAL(name) std::make_shared<Iron::Material>(name)

namespace Iron
{
	class Material;
}

using IEMaterial = std::shared_ptr<Iron::Material>;


namespace Iron
{
	
	class IRON_API Material
	{
		friend class GameObject;

		std::string m_name;
		IETexture2D m_albedo;
		IETexture2D m_albedo2;
		IETexture2D m_ao;
		IETexture2D m_normal;
		IETexture2D m_specular;
		IETexture2D m_height;
		Vector3 m_tint = Vector3(1.0f);
		void ApplyMaterial(const IEShader &shader);
	
	public:
		Material(const std::string &name);
		~Material();

		void SetAlbedo(const IETexture2D &albedo);
		void SetAO(const IETexture2D &ao);
		void SetNormal(const IETexture2D &normal);
		void SetSpecular(const IETexture2D &specular);
		void SetTint(float r, float g, float b);
		const std::string &GetName();
	};

	class MaterialLibrary
	{
	private:	
		std::unordered_map<std::string, IEMaterial> m_materialLib;

	public:
		void Add(const IEMaterial &material);
		IEMaterial &Get(const std::string &name);
		bool Exists(const std::string &name);
	};
}