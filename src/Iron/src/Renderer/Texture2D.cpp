#include "glad/glad.h"
#include "Renderer/Texture2D.hpp"
#include "stb_image.h"

Texture2D::Texture2D(const std::string &type, const char *path, bool invert)
	:m_type(type),
	 m_path(path)
{	
	GlCall(glGenTextures(1, &m_rendererID));
	GlCall(glActiveTexture(GL_TEXTURE0));
	GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
	
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
		}
		else
		{
			IRON_CORE_INFO("[ERROR] Failed to load image");
		}
		stbi_image_free(data);
	}
}

Texture2D::~Texture2D()
{

}

const std::string &Texture2D::GetPath() const 
{
	return m_path;
}

void Texture2D::AddTexture(const std::string &type, const char *path, bool invert)
{
	int height;
	int width;
	int nrChannel;

	stbi_set_flip_vertically_on_load(invert);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannel, 0);

	GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

	GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
	GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
	GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	
	if (data)
	{
		m_path = std::string(path);
		GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, (nrChannel > 3) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data));
		GlCall(glGenerateMipmap(GL_TEXTURE_2D));
		stbi_image_free(data);
	}
	else
	{
		IRON_CORE_INFO("[IRON] Failed to load image");
	}
}

void Texture2D::RemoveTexture() const
{
		GlCall(glDeleteTextures(1, &m_rendererID));
}

void Texture2D::Bind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture2D::Unbind() const
{
	GlCall(glBindTexture(GL_TEXTURE_2D, 0));
}

const std::string &Texture2D::GetType()
{
	return m_type;
}