#include "Renderer/Camera.hpp"
#include "IronEngine.hpp"

namespace Iron
{
	Camera *Camera::s_mainCamera = nullptr;

	Camera &Camera::Main()
	{
		return *s_mainCamera;
	}

	const glm::mat4 &Camera::GetProjectionMat()
	{
		return m_projection;
	}

	// TODO : Return reference?
	const glm::mat4& Camera::GetViewMat()
	{
		m_view = glm::inverse(m_transform.GetMatrix());
		return m_view;
	}

	Transform &Camera::GetTransform() {
		return m_transform;
	}

	void Camera::SetFOV(float fov)
	{
		m_fov = fov;
		m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
	}

	void Camera::SetNearPlane(float nearPlane)
	{
		m_near = nearPlane;
		m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);	
	}

	void Camera::SetFarPlane(float farPlane)
	{
		m_far = farPlane;
		m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
	}

	void Camera::SetAspectRatio(float ratio)
	{
		m_aspectRatio = ratio;
		m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
	}

	void Camera::SetAsMain()
	{
		s_mainCamera = this;
	}

	void Camera::OnEvent(Event &event)
	{
		if (event.GetEventType() == EventType::WindowResize)
		{
			WindowResizeEvent &wr = (WindowResizeEvent&)event;
			m_projection = glm::perspective(glm::radians(m_fov), wr.GetWidth()/wr.GetHeight(), m_near, m_far);
		}
	}
}