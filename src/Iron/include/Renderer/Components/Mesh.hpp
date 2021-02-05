#pragma once
#include "pch.hpp"
#include "Renderer/VertexArray.hpp"

namespace Iron 
{
	class Mesh
	{
	private:
		shared_ptr<VertexArray> m_vertexArray;
	public: 
		void Init();
		Mesh(shared_ptr<VertexArray> &vertexArr);
		Mesh(const Mesh& mesh);
		~Mesh();
		shared_ptr<VertexArray>& GetVertexArray();
	};
}