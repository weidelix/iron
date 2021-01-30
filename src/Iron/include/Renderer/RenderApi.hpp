#pragma once
#include <glm.hpp>
#include <glad/glad.h>

#include "pch.hpp"
#include "Log.hpp"
#include "Core.hpp"
#include "Renderer/VertexArray.hpp"

namespace Iron
{
	class RenderApi
	{
	public:
		RenderApi() { }
		virtual ~RenderApi(){ }
 
		virtual void SetClearColor(const glm::vec4& clearCol){ }
		virtual void Clear(){ }
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArr){ }
	};
}