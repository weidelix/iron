#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Texture2D.hpp"
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
		std::vector<Texture2D> m_textures;

	public: 
		Mesh();
		Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture2D> &textures);
		Mesh(const Mesh& mesh);
		~Mesh();

		void Draw(const std::shared_ptr<Shader> &shader);
		void Setup();
	};
}