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
		static MaterialLibrary m_materialLibrary;

	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArr);
		static void Submit(const IEShader &shader, const std::shared_ptr<VertexArray>& vertexArr);
		static IEShader &LoadShader(const std::string &path);
		static IEShader &LoadShader(const std::string &name, const std::string &path);
		static IEShader &LoadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
		static IEMaterial &CreateMaterial(const std::string &name);
		static void UseDefaultShader();
		static IEShader &GetDefaultShader();
		static IEMaterial &GetDefaultMaterial();
	};

	class ComponentLibrary
	{
	// private:
	// public:
	// 	void Add()
	};
}