#include "Renderer/Camera.hpp"

namespace Iron
{
	Camera Camera::s_mainCamera;

	Camera Camera::Main() 
	{
		return s_mainCamera;
	}

	const glm::mat4 &Camera::GetProjectionMat() const
	{
		return m_projection;
	}

	const glm::mat4 &Camera::GetViewMat() const
	{
		return m_view;
	} 
}