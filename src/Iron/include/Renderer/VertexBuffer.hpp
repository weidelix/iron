#pragma once

#include "Renderer/Renderer.h"

#define TRANSFORM 0
#define TEXT_COORD 1
#define NORMAL 2

namespace Iron
{
	class VertexBuffer
	{
	private: 
		unsigned int m_RendererId;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();

		void BufferData(const void *data, unsigned int size) const;

		void Bind() const;
		void BindVertex(unsigned int bindingIndex, unsigned int offset, unsigned int stride) const;
		void Unbind() const;
	};
}