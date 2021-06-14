#include "Time.hpp"
#include "GLFW/glfw3.h"

namespace  Iron
{
	float Time::s_deltaTime = 0.0f;
	float Time::s_lastFrame = 0.0f;

	void Time::SetDeltaTime()
	{
		float currentFrame = glfwGetTime();
		s_deltaTime = currentFrame - s_lastFrame;
		s_lastFrame = currentFrame;
	}

	float Time::DeltaTime()
	{
		return s_deltaTime;
	}
}