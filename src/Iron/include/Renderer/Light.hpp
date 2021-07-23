#pragma once

#include "Core.hpp"
#include "Renderer/Components/Transform.hpp"

namespace Iron 
{
	class IRON_API Light
	{
	private:
		Transform m_transform;
	public:
		Light();
		~Light();
	};
}