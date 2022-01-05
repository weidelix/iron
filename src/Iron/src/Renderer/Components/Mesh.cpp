#include <glad/glad.h>
#include "Renderer/Components/Mesh.hpp"

namespace Iron
{
	Mesh::Mesh()
	{
		
	}

	Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
		:m_vertexArray(std::make_shared<VertexArray>())
	{
		m_vertices = vertices;
		m_indices  = indices;

		Setup();
	}

	Mesh::Mesh(const Mesh &mesh)
		:m_vertexArray(mesh.m_vertexArray)
	{
		m_vertices = mesh.m_vertices;
		m_indices  = mesh.m_indices;
	
		Setup();
	}
	
	Mesh::~Mesh() 
	{
		
	}

	void Mesh::Setup()
	{
		m_vertexArray->Bind();

		m_vertexArray->GetVertexBuffer().BufferData(&m_vertices[0], m_vertices.size() * sizeof(Vertex));
		m_vertexArray->GetIndexBuffer().BufferData(&m_indices[0], m_indices.size());
		m_vertexArray->GetVertexBuffer().BindVertex(0, 0, sizeof(Vertex));

		VertexArray::EnableVertexAttribArray(0);
		VertexArray::VertexAttribBinding(0, 0);
		m_vertexArray->VertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);

		VertexArray::EnableVertexAttribArray(1);
		VertexArray::VertexAttribBinding(1, 0);
		m_vertexArray->VertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Normal));

		VertexArray::EnableVertexAttribArray(2);
		VertexArray::VertexAttribBinding(2, 0);
		m_vertexArray->VertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, TexCoords));

		m_vertexArray->Unbind();
	}
}