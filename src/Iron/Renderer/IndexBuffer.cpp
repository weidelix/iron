#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) 
	: m_Count(count)
{
	GlCall(glGenBuffers(1, &m_RendererId));
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
	GlCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() 
{
	GlCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}

void IndexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

inline unsigned int IndexBuffer::GetCount() const
{
	return m_Count;
}