#pragma once

#include "Renderer/RenderCommand.hpp"

class IRON_API Texture2D
{
private:
	unsigned int m_rendererID;
	std::string m_type;
	std::string m_path;

public:
	Texture2D(const std::string &type, const char *path = nullptr, bool invert = true);
	~Texture2D();
	
	const std::string &GetPath() const;
	void Bind() const;
	void Unbind() const;
	void AddTexture(const std::string &type, const char *path, bool invert = true);
	void RemoveTexture() const;
	const std::string& GetType();
};