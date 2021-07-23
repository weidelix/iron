#include "glad/glad.h"
#include "Renderer/IndexBuffer.hpp"
#include "Renderer/RenderCommand.hpp"

namespace Iron
{
	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
		: m_Count(count)
	{
		GlCall(glGenBuffers(1, &m_rendererID));
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
		GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	IndexBuffer::~IndexBuffer() 
	{
		GlCall(glDeleteBuffers(1, &m_rendererID));
	}

	void IndexBuffer::SetCount(unsigned int count)
	{
		m_Count = count;
	}

	void IndexBuffer::BufferData(const void* data, unsigned int count)
	{
		m_Count = count;
		Bind();
    GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	void IndexBuffer::Bind() const
	{
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}
}