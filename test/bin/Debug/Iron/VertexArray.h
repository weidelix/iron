#pragma once

#include "Renderer.h"

class VertexArray
{
private: 
	unsigned int m_RendererId;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	static void EnableVertexAttribArray(unsigned int attribIndex);
	static void VertexAttribBinding(unsigned int attribIndex, unsigned int bindingIndex);
	void VertexAttribFormat(unsigned int attribIndex, unsigned int componentCount, unsigned int type, unsigned int normalize, unsigned int attribOffset);
	void Unbind() const;
};