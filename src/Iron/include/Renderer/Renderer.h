 #pragma once

#include "Core.h"
#include "Log.h"
#include <glad/glad.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GlCall(x) GlClearError();\
				  x;\
				  ASSERT(GlLogCall(#x, __FILE__, __LINE__))

void IRON_API GlClearError(); 
bool IRON_API GlLogCall(const char* function, const char* file, int line);