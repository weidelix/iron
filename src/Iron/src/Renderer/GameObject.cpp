#include "Renderer/GameObject.hpp"
#include "Renderer/Renderer.hpp"

namespace Iron
{
	GameObject::GameObject()
		:m_vertexArray(std::make_shared<VertexArray>(nullptr, 0, nullptr, 0)),
		 m_shader(Renderer::GetDefaultShader()),
		 m_transform(m_shader)
	{ 
		Init();
	}

	GameObject::GameObject(const void *vertexBuffer, unsigned int size, const unsigned int *indexBuffer, unsigned int count)
		:m_vertexArray(std::make_shared<VertexArray>(vertexBuffer, size, indexBuffer, count)),
		 m_shader(Renderer::GetDefaultShader()),
		 m_transform(m_shader)
	{
		Init();
	}

	GameObject::GameObject(Mesh& mesh) :m_mesh(mesh) { }

	GameObject::~GameObject() { }

	void GameObject::Init()
	{
		m_vertexArray->Init();		
	}

	void GameObject::Draw() 
	{
		Renderer::Submit(m_vertexArray);
	}

	Transform &GameObject::GetTransform()
	{
		m_shader->Use();
		return m_transform;
	}
	
	//* This won't be implemented until model loading is complete
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
				// This is just a very simple way of drawing a plane in the screen.
				// TODO : Add transform 

				float vBuffer[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f,  0.5f, 0.0f,  0.5f,  0.5f, 0.0f };
				unsigned int iBuffer[] = { 0, 1, 2, 2, 3, 1 };

				return GameObject(vBuffer, 12 * sizeof(float), iBuffer, 6);
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