#pragma once
#include "Renderer/Components/Mesh.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Core.hpp"

namespace Iron
{
	enum Primitives
	{
		Plane,
		Box,
		Sphere,
		Cone,
		Cylinder
	};
	
	class IRON_API GameObject
	{
	private:
		Mesh m_mesh;
		Transform m_transform;

	public:
		GameObject();
		GameObject(const void *vertexBuffer, unsigned int size, const unsigned int *indexBuffer, unsigned int count);
		GameObject(const GameObject &gameObject);
		GameObject(Mesh &mesh);
		~GameObject();
		
		void Draw();
		
		static void Create();
		static GameObject CreateEmpty();
		static GameObject CreatePrimitive(Primitives primitive);
	};
}