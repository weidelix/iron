#include "Renderer.h"
#include <glad/glad.h>

void GlClearError()
{
	while (glad_glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glad_glGetError())
	{
		IRON_CORE_ASSERT(false, "OPENGL ERROR", "{}", error);
		return false;
	}
	return true;
} 