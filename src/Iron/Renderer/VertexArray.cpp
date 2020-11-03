#include "VertexArray.h"

VertexArray::VertexArray()
{
	GlCall(glGenVertexArrays(1, &m_RendererId));
	GlCall(glBindVertexArray(m_RendererId));
}

VertexArray::~VertexArray()
{
	GlCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArray::Bind() const
{
	GlCall(glBindVertexArray(m_RendererId));
}

/* static */ void VertexArray::EnableVertexAttribArray(unsigned int attribIndex)
{
	GlCall(glEnableVertexAttribArray(attribIndex));
}

/* static */ void VertexArray::VertexAttribBinding(unsigned int attribIndex, unsigned int bindingIndex)
{
	GlCall(glVertexAttribBinding(attribIndex, bindingIndex));
}

void VertexArray::VertexAttribFormat(unsigned int attribIndex, unsigned int componentCount, unsigned int type,								   unsigned int normalize,   unsigned int attribOffset)
{
	GlCall(glVertexAttribFormat(attribIndex, componentCount, type, normalize, attribOffset));
}

void VertexArray::Unbind() const
{
	GlCall(glBindVertexArray(0));
}