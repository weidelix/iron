#include "Platform/OpenGL/OpenglApi.hpp"

void GlClearError()
{
	while (glad_glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glad_glGetError())
	{
		IRON_CORE_ASSERT(false, "OPENGL ERROR", "{}", error);
		return false;
	}
	return true;
} 

namespace Iron
{
	OpenglApi::OpenglApi(){ }
	OpenglApi::OpenglApi(RenderApi &api){ }
	OpenglApi::~OpenglApi(){ }

	void OpenglApi::SetClearColor(const glm::vec4& clearCol)
	{
		GlCall(glClearColor(clearCol.x, clearCol.y, clearCol.z, clearCol.w));
	}

	void OpenglApi::Clear()
	{
		GlCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void OpenglApi::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArr)
	{
		GlCall(glDrawElements(GL_TRIANGLES, vertexArr->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}