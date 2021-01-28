#include <glad/glad.h>
#include "Renderer/Components/Mesh.hpp"

namespace Iron
{
	Mesh::Mesh(const void *vertexBuffer, unsigned int size, const unsigned int *indexBuffer, unsigned int count)
	:m_vertexBuffer(vertexBuffer, size), m_indexBuffer(indexBuffer, count)
	{
		Init();
	}

	Mesh::Mesh(const Mesh& mesh)
	:m_vertexArray(mesh.m_vertexArray), m_vertexBuffer(mesh.m_vertexBuffer), m_indexBuffer(mesh.m_indexBuffer)
	{
		Init();
	}
	
	Mesh::~Mesh() { }
	
	void Mesh::Init()
	{
		VertexArray::EnableVertexAttribArray(0);
		VertexArray::VertexAttribBinding(0, 0);
		m_vertexArray->VertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);

		m_vertexBuffer.BindVertex(0, 0, 3 * sizeof(float));		
		m_vertexArray->SetIndexBuffer(&m_indexBuffer);
	}

	std::shared_ptr<VertexArray>& Mesh::GetVertexArray()
	{
		return m_vertexArray;
	}
}