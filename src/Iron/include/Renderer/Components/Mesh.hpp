#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Components/Material.hpp"

namespace Iron 
{
	struct Vertex
	{
		glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
	};

	class Mesh
	{
	private:
		friend class GameObject;

		std::shared_ptr<VertexArray> m_vertexArray;

		// TODO : Optimize vectors
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;

	public: 
		Mesh();
		Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
		Mesh(const Mesh& mesh);
		~Mesh();

		void Setup();
	};
}