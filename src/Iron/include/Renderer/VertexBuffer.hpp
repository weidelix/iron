#pragma once

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
		virtual ~VertexBuffer();

		virtual void BufferData(const void *data, unsigned int size) const;

		virtual void Bind() const;
		virtual void BindVertex(unsigned int bindingIndex, unsigned int offset, unsigned int stride) const;
		virtual void Unbind() const;
	};
}