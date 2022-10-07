#include "Renderer/Renderer.hpp" 
#include "Renderer/Components/Material.hpp"
#include <memory>

namespace Iron
{
	ShaderLibrary Renderer::m_shaderLibrary = ShaderLibrary();
	MaterialLibrary Renderer::m_materialLibrary = MaterialLibrary();

	void Renderer::BeginScene() { }
	void Renderer::EndScene() { }
	
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArr) 
	{ 
		RenderCommand::DrawIndexed(vertexArr);
	}

	void Renderer::Submit(const IEShader &shader, const std::shared_ptr<VertexArray> &vertexArr)
	{
		RenderCommand::DrawIndexed(shader, vertexArr);
	}

	IEShader &Renderer::LoadShader(const std::string &path)
	{
		return m_shaderLibrary.Load(path);
	}
	
	IEShader &Renderer::LoadShader(const std::string &name, const std::string &path)
	{
		return m_shaderLibrary.Load(name, path);
	}

	IEShader &Renderer::LoadShader(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
	{
		return m_shaderLibrary.Load(name, vertexShaderPath, fragmentShaderPath);
	}

	IEMaterial &Renderer::CreateMaterial(const std::string &name)
	{
		m_materialLibrary.Add(CREATE_MATERIAL(name));
		return m_materialLibrary.Get(name);
	}

	void Renderer::UseDefaultShader()
	{
		m_shaderLibrary.Get("default")->Use();
	}

	IEShader &Renderer::GetDefaultShader()
	{
		return m_shaderLibrary.Get("default");
	}

	IEMaterial &Renderer::GetDefaultMaterial()
	{
		return m_materialLibrary.Get("default");
	}
}