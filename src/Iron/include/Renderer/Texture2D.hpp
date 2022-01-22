#pragma once

#include "Renderer/Components/Transform.hpp"
#include "Renderer/RenderCommand.hpp"
#include <memory>

class IRON_API Texture2D
{
private:
	unsigned int m_rendererID;
	std::string m_type;
	std::string m_path;


public:
	Texture2D(const std::string &type, const char *path = nullptr, bool invert = true);
	Texture2D(const unsigned char *image, int width, int height, int channels);
	~Texture2D();
	
	/* static */
	static Texture2D SolidColor(const Iron::Vector3 &color);

	const std::string &GetPath() const;
	void Bind() const;
	void Unbind() const;
	void AddTexture(const std::string &type, const char *path, bool invert = true);
	void RemoveTexture() const;
	const std::string& GetType();
};