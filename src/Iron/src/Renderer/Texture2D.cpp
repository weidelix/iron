#include "Log.hpp"
#include "Renderer/Components/Material.hpp"
#include "Renderer/Components/Transform.hpp"
#include "glad/glad.h"
#include "Renderer/Texture2D.hpp"
#include "stb_image.h"
#include <memory>

namespace Iron 
{
	Texture2D::Texture2D(const std::string &type, const char *path, bool invert)
	:m_type(type),
	 m_path(path)
	{	
		GlCall(glGenTextures(1, &m_rendererID));
		GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
		
		if (path != nullptr)
		{
			int height;
			int width;
			int channels;

			stbi_set_flip_vertically_on_load(invert);

			unsigned char* data = stbi_load(path, &width, &height, &channels, 0);

			GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
			GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			
			if (data)
			{
				if (channels == 4)
				{
					GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
					GlCall(glGenerateMipmap(GL_TEXTURE_2D));
				} 
				else if (channels == 3)
				{
					GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
					GlCall(glGenerateMipmap(GL_TEXTURE_2D));
				}
				else if (channels == 1)
				{
					GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data));
					GlCall(glGenerateMipmap(GL_TEXTURE_2D));
				}
			}
			else
			{
				IRON_CORE_ERROR("Failed to load image");
			}

			GlCall(glBindTexture(GL_TEXTURE_2D, 0));
			stbi_image_free(data);
		}
	}

	Texture2D::Texture2D(const std::string &type, const unsigned char *data, int width, int height, int channels)
			: m_path(""),
				m_type(type)
	{
		GlCall(glGenTextures(1, &m_rendererID));
		GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		if (data)
		{
			if (channels == 4)
			{
				GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
				GlCall(glGenerateMipmap(GL_TEXTURE_2D));
			} 
			else if (channels == 3)
			{
				GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
				GlCall(glGenerateMipmap(GL_TEXTURE_2D));
			}
			else if (channels == 1)
			{
				GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data));
				GlCall(glGenerateMipmap(GL_TEXTURE_2D));
			}
		}
		else
		{
			IRON_CORE_ERROR("Failed to load image");
		}

		GlCall(glBindTexture(GL_TEXTURE_2D, 0));
		delete[] data;
	}

	Texture2D::Texture2D(const std::string &type, const Iron::Vector3 &color)
			: m_path(""),
				m_type(type)
	{
		int size = 1;
		int channels = 4;
		unsigned char *data = new unsigned char[channels * size * size * sizeof(unsigned char)];

		for (unsigned int i = 0; i < size * size; i++) 
		{
			data[i * channels    ] = (unsigned char)(color.GetX() * 255.0f);
			data[i * channels + 1] = (unsigned char)(color.GetY() * 255.0f);
			data[i * channels + 2] = (unsigned char)(color.GetZ() * 255.0f);
			data[i * channels + 3] = (unsigned char)(255.0f);
		}

		GlCall(glGenTextures(1, &m_rendererID));
		GlCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		if (data)
		{
			if (channels == 4)
			{
				GlCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
				GlCall(glGenerateMipmap(GL_TEXTURE_2D));
			} 
		}
		else
		{
			IRON_CORE_ERROR("Failed to load image");
		}

		GlCall(glBindTexture(GL_TEXTURE_2D, 0));
		delete[] data;
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
			IRON_CORE_ERROR("Failed to load image");
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
}