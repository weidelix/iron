#include <glad/glad.h>
#include "Renderer/Components/Mesh.hpp"

namespace Iron
{
	Mesh::Mesh(shared_ptr<VertexArray> &vertexArr)
		:m_vertexArray(vertexArr)
	{
		Init();
	} 

	Mesh::Mesh(const Mesh& mesh)
		:m_vertexArray(mesh.m_vertexArray)
	{
		Init();
	}
	
	Mesh::~Mesh() { }
	
	void Mesh::Init()
	{
		VertexArray::EnableVertexAttribArray(0);
		VertexArray::VertexAttribBinding(0, 0);
		m_vertexArray->VertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);

		m_vertexArray->GetVertexBuffer().Bind();
		m_vertexArray->GetIndexBuffer().Bind();
				
		m_vertexArray->GetVertexBuffer().BindVertex(0, 0, 3 * sizeof(float));		
	}

	shared_ptr<VertexArray>& Mesh::GetVertexArray()
	{
		return m_vertexArray;
	}
}