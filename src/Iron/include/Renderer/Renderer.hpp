#pragma once

#include "Renderer/RenderCommand.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Components/Material.hpp"
#include <memory>

namespace Iron
{
	class Renderer
	{
	private:
		static ShaderLibrary m_shaderLibrary;
		static std::shared_ptr<Material> m_defaultMaterial;

	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArr);
		static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray>& vertexArr);
		static std::shared_ptr<Shader> &LoadShader(const std::string &path);
		static std::shared_ptr<Shader> &LoadShader(const std::string &name, const std::string &path);
		static void UseDefaultShader();
		static std::shared_ptr<Shader> &GetDefaultShader();
		static std::shared_ptr<Material> &GetDefaultMaterial();
	};

	class ComponentLibrary
	{
	// private:
	// public:
	// 	void Add()
	};
}