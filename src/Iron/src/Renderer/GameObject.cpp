#include "Renderer/GameObject.hpp"
#include "Renderer/Renderer.hpp"

namespace Iron
{
	GameObject::GameObject()
		:m_mesh(nullptr, 0, nullptr, 0)
	{ 

	}

	GameObject::GameObject(const void *vertexBuffer, unsigned int size, const unsigned int *indexBuffer, unsigned int count)
		:m_mesh(vertexBuffer, size, indexBuffer, count)
	{

	}

	GameObject::GameObject(Mesh& mesh)
		:m_mesh(mesh)
	{
		
	}

	GameObject::~GameObject() 
	{ 

	}

	void GameObject::Draw() 
	{ 
		m_mesh.GetVertexArray()->Bind();
		Renderer::Submit(m_mesh.GetVertexArray());
	}
	
	// This won't be implemented until model loading is complete
	void GameObject::Create() { }

	GameObject GameObject::CreateEmpty() { return GameObject(); }

	GameObject GameObject::CreatePrimitive(Primitives primitive)
	{
		switch(primitive)
		{
			case Primitives::Plane:
			{
				float pos[] = 
				{
				 -0.5f, -0.5f, 0.0f,
					0.5f, -0.5f, 0.0f,
				 -0.5f,  0.5f, 0.0f,
				  0.5f,  0.5f, 0.0f,
				};

				unsigned int indices[] = 
				{
					0, 1, 2,
					2, 3, 1
				};

				Mesh mesh(pos, 12 * sizeof(float), indices, 6);
				return GameObject(pos, 12 * sizeof(float), indices, 6);
				break;
			}
			case Primitives::Box:
			case Primitives::Cone:
			case Primitives::Cylinder:
			case Primitives::Sphere:
				break;
		}

		return GameObject::CreateEmpty();
	}
}