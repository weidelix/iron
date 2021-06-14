#pragma once 

#include "Core.hpp"

namespace Iron
{
	class IRON_API Time
	{
		static float s_deltaTime;
		static float s_lastFrame;
	public:
		static void SetDeltaTime();
		static float DeltaTime();
	};
}