#include "Renderer/Renderer.hpp" 

namespace Iron
{
	void Renderer::BeginScene() { }
	void Renderer::EndScene() { }
	void Renderer::Submit(const shared_ptr<VertexArray>& vertexArr) 
	{ 
		RenderCommand::DrawIndexed(vertexArr);
	}
}