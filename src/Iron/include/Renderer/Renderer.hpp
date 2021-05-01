#pragma once

#include "Renderer/RenderCommand.hpp"
#include "Renderer/Shader.hpp"

namespace Iron
{
	class Renderer
	{
	private:
		static ShaderLibrary m_shaderLibrary;

	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const shared_ptr<VertexArray>& vertexArr);
		static void Submit(const shared_ptr<Shader> &shader, const shared_ptr<VertexArray>& vertexArr);
		static shared_ptr<Shader> &LoadShader(const string &path);
		static shared_ptr<Shader> &LoadShader(const string &name, const string &path);
		static void UseDefaultShader();
		static shared_ptr<Shader> &GetDefaultShader();
	};
}