#pragma once

#include "Layer.hpp"
#include "Renderer/Camera.hpp"
#include "Event/KeyEvent.hpp"
#include "Input.hpp"
#include "Log.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Time.hpp"

namespace Iron
{
	class Viewport : public Layer
	{
	private: 
		glm::vec3 m_lookAt;
		Camera m_viewportCamera = Camera();
		float m_lastX, m_lastY;
		float m_yaw = 90.0f;
		float m_pitch = 0.0f;
		float m_roll = 0.0f;
		bool m_isHoldingRight = false;
		bool m_isHoldingLeft = false;
		bool m_firstMouse = true;
		Vector3 m_newPos;
	
	public:
		Viewport(const std::string& name);
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
		bool KeyCallback(KeyPressEvent &event);
		bool MouseMoveCallback(MouseMoveEvent &event);
		bool MouseButtonCallback(MouseButtonPressedEvent &event);
		bool MouseReleaseCallback(MouseButtonReleasedEvent &event);
		bool MouseScrollCallback(MouseScrollEvent &event);
	};
}