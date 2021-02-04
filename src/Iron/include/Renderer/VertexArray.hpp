#pragma once

#include "Renderer/IndexBuffer.hpp"
#include "Renderer/VertexBuffer.hpp"

namespace Iron
{
	class VertexArray
	{
	private: 
		unsigned int m_RendererId;
		IndexBuffer* m_indexBuffer = nullptr;
		VertexBuffer* m_vertexBuffer = nullptr;
	public:
		VertexArray();
		~VertexArray();
		
		static VertexArray Create();
		static void EnableVertexAttribArray(unsigned int attribIndex);
		static void VertexAttribBinding(unsigned int attribIndex, unsigned int bindingIndex);
		
		void Bind() const;
		void VertexAttribFormat(unsigned int attribIndex, unsigned int componentCount, unsigned int type, unsigned int normalize, unsigned int attribOffset);
		void SetIndexBuffer(IndexBuffer* indexBuffer);
		IndexBuffer* GetIndexBuffer();
		void SetVertexBuffer(VertexBuffer* vertexBuffer);
		VertexBuffer* GetVertexBuffer();
		void Unbind() const;
	};
}