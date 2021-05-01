#pragma once 
#include "Core.hpp"
#include "Renderer/Transform.hpp"

#include <glm.hpp>

namespace Iron
{
	class IRON_API Camera
	{
	private:
		int m_cameraId;
		bool m_isMain = false;
		mat4 m_projection;
		mat4 m_view;
		Transform m_transform;

		static Camera s_mainCamera;

	public:
		Camera();
		~Camera();

		mat4 &GetProjectionMat();
		mat4 &GetViewMat();
		
		static Camera Main();

	};
}