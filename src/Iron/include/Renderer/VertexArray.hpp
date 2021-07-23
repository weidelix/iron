#pragma once

#include "Renderer/IndexBuffer.hpp"
#include "Renderer/VertexBuffer.hpp"

namespace Iron
{
	class VertexArray
	{
	private: 
		unsigned int m_rendererID;
		IndexBuffer m_indexBuffer;
		VertexBuffer m_vertexBuffer;

	public:
		~VertexArray();
		
		VertexArray();
		VertexArray(const void *vertexBuffer, unsigned int size, const unsigned int *indexBuffer, unsigned int count);
		static void EnableVertexAttribArray(unsigned int attribIndex);
		static void VertexAttribBinding(unsigned int attribIndex, unsigned int bindingIndex);
		
		void Init();
		void Bind() const;
		void Unbind() const;
		void VertexAttribFormat(unsigned int attribIndex, unsigned int componentCount, unsigned int type, unsigned int normalize, unsigned int attribOffset);
		void SetIndexBuffer(IndexBuffer indexBuffer);
		void SetVertexBuffer(VertexBuffer vertexBuffer);
		IndexBuffer& GetIndexBuffer();
		VertexBuffer& GetVertexBuffer();
	};
}