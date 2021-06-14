#include "Renderer/Camera.hpp"
#include "Application.hpp"

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

	const glm::mat4 &Camera::GetViewMat() 
	{
		m_view[3][0] = -dot(m_transform.Right(), m_transform.GetPosition().GetPosition());
		m_view[3][1] = -dot(m_transform.Up(),    m_transform.GetPosition().GetPosition());
		m_view[3][2] = -dot(m_transform.Front(), m_transform.GetPosition().GetPosition());

		// IRON_CORE_INFO(fmt::format("FRONT: x:{0}, y:{1}, z:{2}", m_transform.Front().x, m_transform.Front().y, m_transform.Front().z));
		// IRON_CORE_INFO(fmt::format("UP: x:{0}, y:{1}, z:{2}", m_transform.Up().x, m_transform.Up().y, m_transform.Up().z));

		// m_view = glm::translate(glm::mat4(1.0), {0.0f, 0.0f, 0.0f}); 
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

	void Camera::SetNearPlane(float near)
	{
		m_near = near;		
		m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
	}

	void Camera::SetFarPlane(float far)
	{
		m_far = far;		
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