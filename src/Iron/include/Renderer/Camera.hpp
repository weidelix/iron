#pragma once 
#include "Core.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Event/WindowEvent.hpp"
#include "Log.hpp"
#include <glm.hpp>

namespace Iron
{
	class IRON_API Camera
	{
	private:
		int m_cameraId;
		float m_aspectRatio = (float)800.0/(float)480.0;
		float m_fov = 45.0;
		float m_near = 0.1;
		float m_far = 100.0;
		Transform m_transform;
		glm::mat4 m_projection = glm::perspective(glm::radians(m_fov), m_aspectRatio, m_near, m_far);
		glm::mat4 &m_view = m_transform.GetMatrix();
		
		static Camera *s_mainCamera;

	public:
		Camera() { }
		Camera(bool isMain) { s_mainCamera = this; }
		~Camera() {}

		static Camera &Main();
		const glm::mat4 &GetProjectionMat();
		const glm::mat4 GetViewMat();
		Transform &GetTransform();
		void SetAsMain();
		void SetFOV(float fov);
		void SetNearPlane(float near);
		void SetFarPlane(float far);
		void SetAspectRatio(float ratio);
		void OnEvent(Event &event);
	};
}