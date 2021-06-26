#include <glad/glad.h>
#include "Renderer/Components/Mesh.hpp"

namespace Iron
{
	int Mesh::s_bindingIndex = 0;

	Mesh::Mesh()
	{
		
	}

	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures)
		:m_vertexArray(std::make_shared<VertexArray>())
	{
		m_vertices = vertices;
		m_indices  = indices;
		m_textures = textures;
	}

	Mesh::Mesh(const Mesh& mesh)
		:m_vertexArray(mesh.m_vertexArray)
	{
		m_vertices = mesh.m_vertices;
		m_indices  = mesh.m_indices;
		m_textures = mesh.m_textures;
	}
	
	Mesh::~Mesh() { }

	void Mesh::Setup()
	{
		m_vertexArray->Bind();

		m_vertexArray->GetVertexBuffer().BufferData(&m_vertices[0], m_vertices.size() * sizeof(Vertex));
		m_vertexArray->GetIndexBuffer().BufferData(&m_indices[0], m_indices.size() * sizeof(unsigned int));
		m_vertexArray->GetIndexBuffer().SetCount(m_indices.size());

		VertexArray::EnableVertexAttribArray(0);
		VertexArray::VertexAttribBinding(0, s_bindingIndex);
		m_vertexArray->VertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);

		VertexArray::EnableVertexAttribArray(1);
		VertexArray::VertexAttribBinding(1, s_bindingIndex);
		m_vertexArray->VertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, Normal));

		VertexArray::EnableVertexAttribArray(2);
		VertexArray::VertexAttribBinding(2, s_bindingIndex);
		m_vertexArray->VertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, TexCoords));

		m_vertexArray->GetVertexBuffer().BindVertex(s_bindingIndex, 0, sizeof(Vertex));
		m_vertexArray->Unbind();
		s_bindingIndex++;
	}
}