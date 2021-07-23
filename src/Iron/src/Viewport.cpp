#include "Viewport.hpp"

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
		m_viewportCamera.GetTransform().LookAt(Vector3(0.0f, 0.0f, 6.0f) - Vector3(0.0f));
	}

	void Viewport::OnDetach()
	{
		
	}

	void Viewport::OnUpdate()
	{

	}

	bool Viewport::KeyCallback(KeyPressEvent &event)
	{
		return true;
	}

	bool Viewport::MouseMoveCallback(MouseMoveEvent &event)
	{
		float panSensitivity = 1.0f;
		float rotationSensitivity = 0.3f;

		if (isHoldingLeft)
		{		
			double xpos = event.GetMousePositionX();
			double ypos = event.GetMousePositionY();

			if (firstMouse)
			{
				m_lastX = xpos;
				m_lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - m_lastX;
			float yoffset = m_lastY - ypos; 
			m_lastX = xpos;
			m_lastY = ypos;

			xoffset *= panSensitivity * Time::DeltaTime();
			yoffset *= panSensitivity * Time::DeltaTime();

			Transform &transform = m_viewportCamera.GetTransform();
			Vector3 &pos = transform.GetPosition();
			
			if (xoffset > m_lastX)
				pos = pos + transform.Right() * xoffset;
			else if (xoffset < m_lastX)
				pos = pos - transform.Right() * xoffset;

			if (yoffset < m_lastY)
				pos = pos - transform.Up() * yoffset;
			else if (yoffset > m_lastY)
				pos = pos + transform.Up() * yoffset;

			transform.SetPosition(pos);
		}

		if (isHoldingRight)
		{
			double xpos = event.GetMousePositionX();
			double ypos = event.GetMousePositionY();

			if (firstMouse)
			{
				m_lastX = xpos;
				m_lastY = ypos;
				firstMouse = false;
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
		float offset = event.GetMouseYOffset(); 
		Transform &transform = m_viewportCamera.GetTransform();
		Vector3 &pos = transform.GetPosition();

		if(offset > 0)
			pos = pos - transform.Front() * event.GetMouseYOffset();	
		
		if(offset < 0)
			pos = pos - transform.Front() * event.GetMouseYOffset();	
		
		transform.SetPosition(pos);
		return true;
	}

	bool Viewport::MouseButtonCallback(MouseButtonPressedEvent &event)
	{
		if (event.GetMouseEvent() == Mouse::Mouse_Right)
			isHoldingRight = true;

		else if (event.GetMouseEvent() == Mouse::Mouse_Left)
			isHoldingLeft = true;

		return true;
	}

	bool Viewport::MouseReleaseCallback(MouseButtonReleasedEvent &event)
	{
		if (event.GetMouseEvent() == Mouse::Mouse_Right)
		{
			firstMouse = true;
			isHoldingRight = false;
		}
		else if (event.GetMouseEvent() == Mouse::Mouse_Left)
		{
			firstMouse = true;
			isHoldingLeft = false;
		}
		return true;
	}

	void Viewport::OnEvent(Event& event)
	{;
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<KeyPressEvent>(bind(&Viewport::KeyCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMoveEvent>(bind(&Viewport::MouseMoveCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonPressedEvent>(bind(&Viewport::MouseButtonCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(bind(&Viewport::MouseReleaseCallback, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrollEvent>(bind(&Viewport::MouseScrollCallback, this, std::placeholders::_1));
	}
}