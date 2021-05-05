#pragma once 
#include "Core.hpp"
#include "Renderer/Components/Transform.hpp"

#include <glm.hpp>

namespace Iron
{
	class IRON_API Camera
	{
	private:
		int m_cameraId;
		bool m_isMain = false;
		glm::mat4 m_projection;
		glm::mat4 m_view;
		Transform m_transform;

		static Camera s_mainCamera;

	public:
		Camera() = default;
		~Camera() = default;

		const glm::mat4 &GetProjectionMat() const;
		const glm::mat4 &GetViewMat() const;
		
		static Camera Main();

	};
}