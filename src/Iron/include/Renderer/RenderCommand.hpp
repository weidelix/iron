#pragma once

#include "pch.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Camera.hpp"
#include "glm.hpp"
#include "Log.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) GlClearError();\
				x;\
				ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void IRON_API GlClearError(); 
bool IRON_API GlLogCall(const char* function, const char* file, int line);

namespace Iron 
{
	class RenderCommand
	{
	public:
		static void SetClearColor(const glm::vec4& clearCol);
		static void Clear();
		static void DrawIndexed(const shared_ptr<VertexArray> &vertexArr);
		static void DrawIndexed(const shared_ptr<Shader> &shader, const shared_ptr<VertexArray> &vertexArr);
	};
}