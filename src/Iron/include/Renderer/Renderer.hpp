#pragma once

#include "Renderer/RenderCommand.hpp"

namespace Iron
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArr);
	};
}