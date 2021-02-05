#pragma once
#include "Renderer/RenderApi.hpp"
#include "Platform/OpenGL/OpenglApi.hpp"

namespace Iron 
{
	enum Api
	{
		OpenGL,
		DirectX,
	};

	class RenderCommand
	{
	public:
		static RenderApi *s_api;

	public:
		static void SetClearColor(const glm::vec4& clearCol);
		static void Clear();
		static void DrawIndexed(const shared_ptr<VertexArray>& vertexArr);
		static void UseRenderer(Api api);
	};
}