#include "glad/glad.h"
#include "Renderer/Texture2D.hpp"
#include "stb_image.h"

Texture2D::Texture2D(const char *path, int textureUnit, bool invert)
{
	GlCall(glGenTextures(1, &m_RendererId));
	GlCall(glActiveTexture(GL_TEXTURE0 + textureUnit));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	if (path != nullptr)
	{
		int height;
		int width;
		int nrChannel;

		stbi_set_flip_vertically_on_load(invert);

		unsigned char* data = stbi_load(path, &width, &height, &nrChannel, 0);

		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		if (data)
		{
			GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, (nrChannel > 3) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data));
			GlCall(glGenerateMipmap(GL_TEXTURE_2D));
			stbi_image_free(data);
		}
		else
		{
			std::cout << "[ERROR] Failed to load image" << std::endl;
		}
	}
}

Texture2D::~Texture2D()
{
	GlCall(glDeleteTextures(1, &m_RendererId));
}

void Texture2D::AddTexture(const char *path, int textureUnit, bool invert) const
{
	int height;
	int width;
	int nrChannel;

	stbi_set_flip_vertically_on_load(invert);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannel, 0);

	GlCall(glActiveTexture(GL_TEXTURE0 + textureUnit));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));

	GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	
	if (data)
	{
		GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, (nrChannel > 3) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data));
		GlCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(data);
	}
	else
	{
		std::cout << "[FAIL] Failed to load image" << std::endl;
	}
}

void Texture2D::UseTexture(int textureUnit) const
{
	GlCall(glActiveTexture(GL_TEXTURE0 + textureUnit));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture2D::Bind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, m_RendererId));
}

void Texture2D::Unbind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}