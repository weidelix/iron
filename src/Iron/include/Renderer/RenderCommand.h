#pragma once
#include "pch.h"
#include	"VertexArray.h"

#include <glm.hpp>
#include <glad/glad.h>

namespace Iron 
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& clearCol)
		{
			glClearColor(clearCol.x, clearCol.y, clearCol.z, clearCol.w);
		}

		inline static void Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArr)
		{
			glDrawElements(GL_TRIANGLES, vertexArr->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		}
	};
}