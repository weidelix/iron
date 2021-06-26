#include "Renderer/GameObject.hpp"
#include "Renderer/Renderer.hpp"

namespace Iron
{
	GameObject::GameObject()
		:m_mesh(),
		 m_shader(Renderer::GetDefaultShader())
	{ 
		Init();
	}

	// TODO : Remove
	GameObject::GameObject(const void *vertexBuffer, unsigned int size, 
												 const unsigned int *indexBuffer, unsigned int count)
		:m_mesh(),
		 m_shader(Renderer::GetDefaultShader())
	{
		Init();
	}

	GameObject::GameObject(const Mesh &mesh) 
		:m_mesh(mesh),
		 m_shader(Renderer::GetDefaultShader())
	{
		Init();
	}

	GameObject::~GameObject() { }

	void GameObject::Init()
	{
		m_mesh.Setup();
	}

	void GameObject::Draw() 
	{
		m_shader->SetMat4x4("model", m_transform.GetMatrix());
		Renderer::Submit(m_shader, m_mesh.m_vertexArray);
	}

	Transform &GameObject::GetTransform()
	{
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
				std::vector<Vertex> vBuffer = {
																				{{-1.0f,  0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, -1.0f}}, 
																				{{ 1.0f,  0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f, -1.0f}}, 
																				{{-1.0f,  0.0f,-1.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f,  1.0f}}, 
																				{{ 1.0f,  0.0f,-1.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f,  1.0f}}
																			};

				std::vector<unsigned int> iBuffer = { 0, 1, 2, 2, 3, 1 };
				std::vector<Texture2D> tBuffer = { Texture2D() };

				return GameObject(Mesh(vBuffer, iBuffer, tBuffer));
				break;
			}
			// NOTE : Temporary
			case Primitives::Cube:
			{
				std::vector<Vertex> vBuffer = {
																				{{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f, -1.0f}}, 
																				{{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f, -1.0f}}, 
																				{{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {-1.0f,  1.0f}}, 
																				{{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f,  1.0f}},
																				{{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f,  1.0f}},
																				{{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f,  1.0f}},
																				{{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f,  1.0f}},
																				{{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f,  1.0f}}
																			};

				std::vector<unsigned int> iBuffer = { 
																							0, 1, 2, 2, 3, 0, 
																							4, 5, 6, 6, 7, 4, 
																							4, 0, 3, 3, 7, 4,
																							5, 1, 2, 2, 6, 5,
																							3, 2, 6, 6, 7, 3,
																							0, 1, 5, 5, 4, 0
																						};
				std::vector<Texture2D> tBuffer = { Texture2D() };

				return GameObject(Mesh(vBuffer, iBuffer, tBuffer));
				break;
			}
			case Primitives::Cone:
			case Primitives::Cylinder:
			case Primitives::Sphere:
				break;
		}

		return GameObject::CreateEmpty();
	}
}