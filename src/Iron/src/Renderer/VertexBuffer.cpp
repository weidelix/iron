#include "Renderer/VertexBuffer.h"

namespace Iron
{
	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		GlCall(glGenBuffers(1, &m_RendererId));
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
		GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer() 
	{
		GlCall(glDeleteBuffers(1, &m_RendererId));
	}

	void VertexBuffer::BufferData(const void* data, unsigned int size) const
	{
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
		GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	void VertexBuffer::Bind() const
	{
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
	}

	void VertexBuffer::BindVertex(unsigned int bindingIndex, unsigned int offset, unsigned int stride) const
	{
		GlCall(glBindVertexBuffer(bindingIndex, m_RendererId, offset, stride));
	}

	void VertexBuffer::Unbind() const
	{
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}
