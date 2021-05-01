#include "Renderer/Renderer.hpp" 

namespace Iron
{
	ShaderLibrary Renderer::m_shaderLibrary = ShaderLibrary();

	void Renderer::BeginScene() { }
	void Renderer::EndScene() { }
	
	void Renderer::Submit(const shared_ptr<VertexArray>& vertexArr) 
	{ 
		RenderCommand::DrawIndexed(vertexArr);
	}

	void Renderer::Submit(const shared_ptr<Shader> &shader, const shared_ptr<VertexArray> &vertexArr)
	{
		RenderCommand::DrawIndexed(shader, vertexArr);
	}

	shared_ptr<Shader> &Renderer::LoadShader(const string &path)
	{
		return m_shaderLibrary.Load(path);
	}
	
	shared_ptr<Shader> &Renderer::LoadShader(const string &name, const string &path)
	{
		return m_shaderLibrary.Load(name, path);
	}

	void Renderer::UseDefaultShader()
	{
		m_shaderLibrary.Get("default")->Use();
	}

	shared_ptr<Shader> &Renderer::GetDefaultShader()
	{
		return m_shaderLibrary.Get("default");
	}
}