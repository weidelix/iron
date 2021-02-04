#pragma once
#include "pch.hpp"
#include "Renderer/VertexArray.hpp"

namespace Iron 
{
	class Mesh
	{
	private:
		std::shared_ptr<VertexArray> m_vertexArray = std::make_shared<VertexArray>();
		VertexBuffer m_vertexBuffer;
		IndexBuffer m_indexBuffer;
	public: 
		void Init();
		Mesh(const void *vertexBuffer, unsigned int size, const unsigned int* indexBuffer, unsigned int count);
		Mesh(const Mesh& mesh);
		~Mesh();
		std::shared_ptr<VertexArray>& GetVertexArray();
	};
}