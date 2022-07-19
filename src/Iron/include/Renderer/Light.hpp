#pragma once

#include "Core.hpp"
#include "Renderer/Components/Transform.hpp"

namespace Iron 
{
	class IRON_API Light
	{
	private:
		Transform m_transform;
		Vector3 m_color;


	public:
		Light();
		~Light();

		
	};
}