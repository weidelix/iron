#pragma once 

#include "Core.hpp"

namespace Iron
{
	class IRON_API Time
	{
		static float s_deltaTime;
		static float s_lastFrame;
		static float s_timeElapsed;
	public:
		#ifdef IRON_BUILD_DLL
			static void SetDeltaTime();
		#endif
		static float DeltaTime();
		static float TimeElapsed();
	};
}