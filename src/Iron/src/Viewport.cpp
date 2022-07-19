#include "Viewport.hpp"
#include "Log.hpp"
#include "Renderer/Components/Transform.hpp"

namespace Iron
{
	Viewport::Viewport(const std::string& name)
		:Layer(name)
	{

	}
	
	void Viewport::OnAttach()
	{
		m_viewportCamera.SetAsMain();
		m_viewportCamera.GetTransform().SetPosition(Vector3(0.0f, 0.0f, 6.0f));
		m_newPos = m_viewportCamera.GetTransform().GetPosition();
		m_viewportCamera.GetTransform().LookAt(Vector3(0.0f, 0.0f, 6.0f) - Vector3(0.0f));
	}

	void Viewport::OnDetach()
	{
		
	}

	void Viewport::OnUpdate()
	{
		auto &transform = m_viewportCamera.GetTransform();
		auto curPos = transform.GetPosition();
		transform.SetPosition(curPos + (m_newPos - curPos) * 0.2f);
	}

	bool Viewport::KeyCallback(KeyPressEvent &event)
	{
		return true;
	}

	bool Viewport::MouseMoveCallback(MouseMoveEvent &event)
	{
		float panSensitivity = 1.0f;
		float rotationSensitivity = 0.3f;

		if (m_isHoldingLeft)
		{		
			double xpos = event.GetMousePositionX();
			double ypos = event.GetMousePositionY();
			if (m_firstMouse)
			{
				m_lastX = xpos;
				m_lastY = ypos;
				m_firstMouse = false;
			}

			float xoffset = xpos - m_lastX;
			float yoffset = m_lastY - ypos; 
			m_lastX = xpos;
			m_lastY = ypos;

			xoffset *= panSensitivity * Time::DeltaTime();
			yoffset *= panSensitivity * Time::DeltaTime();

			Transform &transform = m_viewportCamera.GetTransform();
			Vector3 pos = transform.GetPosition();
			
			if (xoffset > m_lastX)
				pos = pos + transform.Right() * xoffset;
			else if (xoffset < m_lastX)
				pos = pos - transform.Right() * xoffset;

			if (yoffset < m_lastY)
				pos = pos - transform.Up() * yoffset;
			else if (yoffset > m_lastY)
				pos = pos + transform.Up() * yoffset;

			m_newPos = pos;
		}

		if (m_isHoldingRight)
		{
			double xpos = event.GetMousePositionX();
			double ypos = event.GetMousePositionY();

			if (m_firstMouse)
			{
				m_lastX = xpos;
				m_lastY = ypos;
				m_firstMouse = false;
			}
		
			float xoffset = xpos - m_lastX;
			float yoffset = m_lastY - ypos;
			m_lastX = xpos;
			m_lastY = ypos;

			xoffset *= rotationSensitivity;
			yoffset *= rotationSensitivity;

			m_yaw += xoffset;
			m_pitch -= yoffset;

			if(m_pitch > 89.0f)
					m_pitch = 89.0f;
			if(m_pitch < -89.0f)
					m_pitch = -89.0f;

			Vector3 direction;
			direction.SetX(cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
			direction.SetY(sin(glm::radians(m_pitch)));
			direction.SetZ(sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
			
			m_viewportCamera.GetTransform().LookAt(Vector3::Normalize(direction));
		}
		return true;
	}

	bool Viewport::MouseScrollCallback(MouseScrollEvent &event)
	{
		float scrollSensitivity = 1.5f;
		float offset = event.GetMouseYOffset(); 
		Transform &transform = m_viewportCamera.GetTransform();
		Vector3 position = transform.GetPosition();

		m_newPos = position - transform.Front() * offset * scrollSensitivity;
		return true;
	}

	bool Viewport::MouseButtonCallback(MouseButtonPressedEvent &event)
	{
		m_isHoldingRight = event.GetMouseEvent() == Mouse::Mouse_Right;
		m_isHoldingLeft = event.GetMouseEvent() == Mouse::Mouse_Left;
		return true;
	}

	bool Viewport::MouseReleaseCallback(MouseButtonReleasedEvent &event)
	{
		m_firstMouse = true;
		m_isHoldingRight = false;
		m_isHoldingLeft = false;
		return true;
	}

	void Viewport::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<KeyPressEvent>(bind(&Viewport::KeyCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMoveEvent>(bind(&Viewport::MouseMoveCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(bind(&Viewport::MouseButtonCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(bind(&Viewport::MouseReleaseCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrollEvent>(bind(&Viewport::MouseScrollCallback, this, std::placeholders::_1));
	}
}