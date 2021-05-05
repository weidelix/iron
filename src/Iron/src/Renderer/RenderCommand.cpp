#include "glad/glad.h"
#include "Renderer/RenderCommand.hpp"
#include "Renderer/Renderer.hpp"

void GlClearError()
{
	while (glad_glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glad_glGetError())
	{
		IRON_CORE_ASSERT(false, "OPENGL ERROR {0}", error);
		return false;
	}
	return true;
} 

namespace Iron
{
	void RenderCommand::SetClearColor(const glm::vec4& clearCol)
	{
		GlCall(glClearColor(clearCol.x, clearCol.y, clearCol.z, clearCol.w));			
	}

	void RenderCommand::Clear()
	{
		GlCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArr)
	{
		Renderer::UseDefaultShader();
		const std::shared_ptr<Shader> &shader = Renderer::GetDefaultShader();
		
		const Camera &mainCamera = Camera::Main();
		shader->SetMat4x4("projection", mainCamera.GetProjectionMat());
		shader->SetMat4x4("view", mainCamera.GetViewMat());
		
		vertexArr->Bind();
		GlCall(glDrawElements(GL_TRIANGLES, vertexArr->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArr)
	{
		shader->Use();

		const Camera& mainCamera = Camera::Main();
		shader->SetMat4x4("projection", mainCamera.GetProjectionMat());
		shader->SetMat4x4("view", mainCamera.GetViewMat());

		vertexArr->Bind();
		GlCall(glDrawElements(GL_TRIANGLES, vertexArr->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
	}
}