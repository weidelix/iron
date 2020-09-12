#pragma once
#include <string>
#include <iostream>

#include "Renderer.h"
#include "glad/glad.h"

class Texture2D
{
private:
	unsigned int m_RendererId;
	int m_TexUnit = 0;

public:
	// Default Texture Unit is GL_TEXTURE0
	Texture2D(const char *path = nullptr, int textureUnit = 0, bool invert = false);
	~Texture2D();

	void Bind() const;
	void Unbind() const;
	void AddTexture(const char *path, int textureUnit = 0, bool invert = false) const;
	void UseTexture(int textureUnit) const;
};

