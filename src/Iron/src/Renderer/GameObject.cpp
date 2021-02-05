#include "Renderer/GameObject.hpp"
#include "Renderer/Renderer.hpp"

namespace Iron
{
	GameObject::GameObject()
		:m_mesh(make_shared<VertexArray>(nullptr, 0, nullptr, 0))
	{ 

	}

	GameObject::GameObject(const void *vertexBuffer, unsigned int size, const unsigned int *indexBuffer, unsigned int count)
		:m_mesh(make_shared<VertexArray>(vertexBuffer, size, indexBuffer, count))
	{
		
	}

	GameObject::GameObject(const GameObject &gameObject)
		:m_mesh(gameObject.m_mesh)
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
	
	//*This won't be implemented until model loading is complete
	//* Might be replaced with "Model::Load"
	/* static */
	void GameObject::Create() { }

	/* static */
	GameObject GameObject::CreateEmpty() { return GameObject(); }

	/* static */
	GameObject GameObject::CreatePrimitive(Primitives primitive)
	{
		switch(primitive)
		{
			case Primitives::Plane:
			{
				return GameObject((float[]) 
				{
					-0.5f, -0.5f, 0.0f,
					 0.5f, -0.5f, 0.0f,
					-0.5f,  0.5f, 0.0f,
					 0.5f,  0.5f, 0.0f,
				}, 12 * sizeof(float), (unsigned int[])
				{
					0, 1, 2,
					2, 3, 1
				}, 6);
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