#include "Renderer/VertexArray.h"

namespace Iron
{
	VertexArray::VertexArray()
	{
		GlCall(glGenVertexArrays(1, &m_RendererId));
		GlCall(glBindVertexArray(m_RendererId));
	}

	VertexArray::~VertexArray()
	{
		GlCall(glDeleteVertexArrays(1, &m_RendererId));
	}

	VertexArray VertexArray::Create()
	{
		return VertexArray();
	}

	void VertexArray::Bind() const
	{
		GlCall(glBindVertexArray(m_RendererId));
	}

	/* static */ 
	void VertexArray::EnableVertexAttribArray(unsigned int attribIndex)
	{
		GlCall(glEnableVertexAttribArray(attribIndex));
	}

	/* static */ 
	void VertexArray::VertexAttribBinding(unsigned int attribIndex, unsigned int bindingIndex)
	{
		GlCall(glVertexAttribBinding(attribIndex, bindingIndex));
	}

	void VertexArray::VertexAttribFormat(unsigned int attribIndex, unsigned int componentCount, unsigned int type,								   unsigned int normalize,   unsigned int attribOffset)
	{
		GlCall(glVertexAttribFormat(attribIndex, componentCount, type, normalize, attribOffset));
	}

	void VertexArray::SetIndexBuffer(IndexBuffer* indexBuffer)
	{
		m_indexBuffer = indexBuffer;
	}

	IndexBuffer* VertexArray::GetIndexBuffer()
	{
		return m_indexBuffer;
	}

	void VertexArray::SetVertexBuffer(VertexBuffer* vertexBuffer)
	{
		m_vertexBuffer = vertexBuffer;
	}

	VertexBuffer* VertexArray::GetVertexBuffer()
	{
		return m_vertexBuffer;
	}

	void VertexArray::Unbind() const
	{
		GlCall(glBindVertexArray(0));
	}
}