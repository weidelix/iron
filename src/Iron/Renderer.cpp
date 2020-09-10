#include "Renderer.h"
#include <iostream>

void GlClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		system("color 03");
		std::cout << "[GL-ERROR]";
		system("color 0f");
		std::cout<< "(" << error << ") " << function << " " << file << " : " << line << std::endl;
		return false;
	}
	return true;
} 