#include <glad/glad.h>
#include "Renderer/Components/Mesh.hpp"

namespace Iron
{
	Mesh::Mesh()
	{
		
	}

	Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture2D> &textures)
		:m_vertexArray(std::make_shared<VertexArray>())
	{
		m_vertices = vertices;
		m_indices  = indices;
		m_textures = textures;

		Setup();
	}

	Mesh::Mesh(const Mesh &mesh)
		:m_vertexArray(mesh.m_vertexArray)
	{
		m_vertices = mesh.m_vertices;
		m_indices  = mesh.m_indices;
		m_textures = mesh.m_textures;
	
		Setup();
	}
	
	Mesh::~Mesh() 
	{
		for (auto t : m_textures)
		{
			t.RemoveTexture();
		}
	}

	void Mesh::Draw(const std::shared_ptr<Shader> &shader)
	{
		unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
		for (unsigned int i = 0; i < m_textures.size(); i++)
    {	
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			std::string name = m_textures[i].GetType();

			if(name == "texture_diffuse")
			    number = std::to_string(diffuseNr++);
			else if(name == "texture_specular")
			    number = std::to_string(specularNr++);

			m_textures[i].Bind();
			shader->SetInt1(("fMaterial." + name + number).c_str(), i);
		}
		GlCall(glActiveTexture(GL_TEXTURE0));
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