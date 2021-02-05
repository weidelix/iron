#include "Renderer/RenderCommand.hpp"

namespace Iron
{
	RenderApi *RenderCommand::s_api = new OpenglApi();

	void RenderCommand::SetClearColor(const glm::vec4& clearCol)
	{
		s_api->SetClearColor(clearCol);			
	}

	void RenderCommand::Clear()
	{
		s_api->Clear();
	}

	void RenderCommand::DrawIndexed(const shared_ptr<VertexArray>& vertexArr)
	{
		s_api->DrawIndexed(vertexArr);
	}

	void RenderCommand::UseRenderer(Api api)
	{
		switch(api)
		{
			case Api::OpenGL:
			{
				s_api = dynamic_cast<OpenglApi*>(s_api);
				break;
			}
			case Api::DirectX:
			{
				IRON_CORE_INFO("DirectX isn't available right now");
				break;
			}
		};
	}
}