#pragma once

#include <glm.hpp>
#include <glad/glad.h>

#include "pch.hpp"
#include "Log.hpp"
#include "Core.hpp"
#include "Renderer/VertexArray.hpp"

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
		inline static void SetClearColor(const glm::vec4& clearCol)
		{
			GlCall(glClearColor(clearCol.x, clearCol.y, clearCol.z, clearCol.w));
		}

		inline static void Clear()
		{
			GlCall(glClear(GL_COLOR_BUFFER_BIT));
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArr)
		{
			GlCall(glDrawElements(GL_TRIANGLES, vertexArr->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
		}
	};
}