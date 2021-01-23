#pragma once
#include "Renderer/RenderApi.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) GlClearError();\
				x;\
				ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void IRON_API GlClearError(); 
bool IRON_API GlLogCall(const char* function, const char* file, int line);

namespace Iron
{
	class OpenglApi : public RenderApi
	{
	public:
		OpenglApi();
		OpenglApi(RenderApi &api);
		~OpenglApi();

		void SetClearColor(const glm::vec4& clearCol) override;
		void Clear() override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArr) override;
	};
}