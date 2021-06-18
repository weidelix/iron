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
		m_viewportCamera.GetTransform().SetPosition({0.0, 0.0, 3.0});

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		direction.y = sin(glm::radians(m_pitch));
		direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

		m_viewportCamera.GetTransform().LookAt(glm::normalize(direction));
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
		float sensitivity = 0.3f;

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

			xoffset *= sensitivity * Time::DeltaTime();
			yoffset *= sensitivity * Time::DeltaTime();

			Transform &transform = m_viewportCamera.GetTransform();
			Position &pos = transform.GetPosition();
			
			if (xoffset > m_lastX)
				pos.SetPosition(pos.GetPosition() + xoffset * transform.Right());
			else if (xoffset < m_lastX)
				pos.SetPosition(pos.GetPosition() - xoffset * transform.Right());

			if (yoffset < m_lastY)
				pos.SetPosition(pos.GetPosition() - yoffset * transform.Up());
			else if (yoffset > m_lastY)
				pos.SetPosition(pos.GetPosition() + yoffset * transform.Up());

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

			xoffset *= sensitivity;
			yoffset *= sensitivity;

			m_yaw += xoffset;
			m_pitch += yoffset;

			if(m_pitch > 89.0f)
					m_pitch = 89.0f;
			if(m_pitch < -89.0f)
					m_pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
			direction.y = sin(glm::radians(m_pitch));
			direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

			m_viewportCamera.GetTransform().LookAt(glm::normalize(direction));
		}
		return true;
	}

	bool Viewport::MouseScrollCallback(MouseScrollEvent &event)
	{
		float offset = event.GetMouseYOffset(); 
		Transform &transform = m_viewportCamera.GetTransform();
		Position &pos = transform.GetPosition();

		if(offset > 0)
			pos.SetPosition(pos.GetPosition() - transform.Front() * event.GetMouseYOffset());	
		
		if(offset < 0)
			pos.SetPosition(pos.GetPosition() - transform.Front() * event.GetMouseYOffset());	
		
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