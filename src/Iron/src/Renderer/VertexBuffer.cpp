#include "glad/glad.h"
#include "Renderer/VertexBuffer.hpp"
#include "Renderer/RenderCommand.hpp"

namespace Iron
{
	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		GlCall(glGenBuffers(1, &m_rendererID));
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
		GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	VertexBuffer::~VertexBuffer() 
	{
		GlCall(glDeleteBuffers(1, &m_rendererID));
	}

	void VertexBuffer::BufferData(const void* data, unsigned int size) const
	{
		Bind();
		GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

	void VertexBuffer::Bind() const
	{
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
	}

	void VertexBuffer::BindVertex(unsigned int bindingIndex, unsigned int offset, unsigned int stride) const
	{
		GlCall(glBindVertexBuffer(bindingIndex, m_rendererID, offset, stride));
	}

	void VertexBuffer::Unbind() const
	{
		GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}
