#pragma once

#include "Renderer/Components/Transform.hpp"
#include "Renderer/RenderCommand.hpp"
#include "Renderer/Texture2D.hpp"
#include <memory>

namespace Iron 
{
	class Texture2D;
}

using IETexture2D = std::shared_ptr<Iron::Texture2D>;
#define CREATE_TEXTURE2D_PATH(type, path, invert) std::make_shared<Iron::Texture2D>(type, path, invert)
#define CREATE_TEXTURE2D_FROM_DATA(type, image, width, height, channels) std::make_shared<Iron::Texture2D>(type, image, width, height, channels)
#define CREATE_TEXTURE2D_COLOR(type, color) std::make_shared<Iron::Texture2D>(type, color)

namespace Iron 
{
	class IRON_API Texture2D
	{
	private:
		unsigned int m_rendererID;
		std::string m_type;
		std::string m_path;


	public:
		Texture2D(const std::string &type, const char *path = nullptr, bool invert = true);
		Texture2D(const std::string &type, const unsigned char *image, int width, int height, int channels);
		Texture2D(const std::string &type, const Iron::Vector3 &color);
		~Texture2D();

		const std::string &GetPath() const;
		void Bind() const;
		void Unbind() const;
		void AddTexture(const std::string &type, const char *path, bool invert = true);
		void RemoveTexture() const;
		void SetType(const std::string &type);
		const std::string& GetType();
	};
}
