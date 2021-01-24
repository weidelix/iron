#pragma once
#include "Renderer/Components/Mesh.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Renderer/RenderCommand.hpp"

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
	
	class GameObject
	{
	private:
		GameObject();
		Mesh m_mesh;
		Transform m_transform;
	public:
		~GameObject();

		// This won't be implemented until model loading is complete
		void Draw() { }
		
		static void Create() { }
		
		static GameObject CreateEmpty() { return GameObject(); }
		
		static GameObject CreatePrimitive(Primitives primitive)
		{
			switch(primitive)
			{
				case Primitives::Plane:
				{
					return GameObject();
					break;
				}
			}

			return GameObject::CreateEmpty();
		}
	};
}