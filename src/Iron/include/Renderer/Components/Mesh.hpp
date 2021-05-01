#pragma once

#include "pch.hpp"
#include "Core.hpp"
#include "Renderer/VertexArray.hpp"

namespace Iron 
{
	class Mesh
	{
	public: 
		Mesh();
		Mesh(const Mesh& mesh);
		~Mesh();
	};
}