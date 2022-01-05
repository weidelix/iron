#include "Renderer/Renderer.hpp" 
#include "Renderer/Components/Material.hpp"
#include <memory>

namespace Iron
{
	ShaderLibrary Renderer::m_shaderLibrary = ShaderLibrary();

	std::shared_ptr<Material> Renderer::m_defaultMaterial = std::make_shared<Material>(); 

	void Renderer::BeginScene() { }
	void Renderer::EndScene() { }
	
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArr) 
	{ 
		RenderCommand::DrawIndexed(vertexArr);
	}

	void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArr)
	{
		RenderCommand::DrawIndexed(shader, vertexArr);
	}

	std::shared_ptr<Shader> &Renderer::LoadShader(const std::string &path)
	{
		return m_shaderLibrary.Load(path);
	}
	
	std::shared_ptr<Shader> &Renderer::LoadShader(const std::string &name, const std::string &path)
	{
		return m_shaderLibrary.Load(name, path);
	}

	void Renderer::UseDefaultShader()
	{
		m_shaderLibrary.Get("default")->Use();
	}

	std::shared_ptr<Shader> &Renderer::GetDefaultShader()
	{
		return m_shaderLibrary.Get("default");
	}

	std::shared_ptr<Material> &Renderer::GetDefaultMaterial()
	{
		return m_defaultMaterial;
	}
}