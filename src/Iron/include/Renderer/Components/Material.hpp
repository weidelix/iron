#pragma once

#include "Core.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Renderer/Texture2D.hpp"
#include "Renderer/Shader.hpp"
#include "assimp/material.h"
#include "pch.hpp"
#include <memory>

#define TEX_AO std::string("texture_ao")
#define TEX_ALBEDO std::string("texture_diffuse")
#define TEX_ALBEDO2 std::string("texture_diffuse2")
#define TEX_NORMALS std::string("texture_normals")
#define TEX_HEIGHT std::string("texture_height")

namespace Iron
{
	class IRON_API Material
	{
		std::shared_ptr<Texture2D> m_albedo;
		std::shared_ptr<Texture2D> m_albedo2;
		std::shared_ptr<Texture2D> m_ao;
		std::shared_ptr<Texture2D> m_normalMap;
		std::shared_ptr<Texture2D> m_heightMap;
		Vector3 m_tint;
		float m_tintA;
		

	public:
		Material();
		~Material();

		void SetAlbedo(const std::shared_ptr<Texture2D> &albedo);
		void SetAO(const std::shared_ptr<Texture2D> &ao);
		void SetTint(float r, float g, float b, float a);
		void ApplyMaterial(const std::shared_ptr<Shader> &shader);
	};
}