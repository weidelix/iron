#pragma once
#include "Renderer/Components/Mesh.hpp"
#include "Renderer/Components/Transform.hpp"

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
		std::shared_ptr<VertexArray> m_vertexArray;
		std::shared_ptr<Shader> m_shader;
		Mesh m_mesh;
		Transform m_transform;

		GameObject();
		GameObject(const void *vertexBuffer, unsigned int size, const unsigned int *indexBuffer, unsigned int count);
	
	public:
		GameObject(Mesh &mesh);
		~GameObject();
		
		void Init();
		void Draw();
		Transform& GetTransform();
		
		static void Create();
		static GameObject CreateEmpty();
		static GameObject CreatePrimitive(Primitives primitive);
	};
}