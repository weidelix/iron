#include "Log.hpp"
#include "Renderer/Components/Material.hpp"
#include "Renderer/Texture2D.hpp"
#include "assimp/material.h"
#include "assimp/mesh.h"
#include "glad/glad.h"
#include "Renderer/GameObject.hpp"
#include "Renderer/Renderer.hpp"
#include <memory>
#include <xmemory>

namespace Iron
{
	GameObject::GameObject()
		:m_meshes(),
		 m_shader(Renderer::GetDefaultShader()),
		 m_material(Renderer::GetDefaultMaterial())
	{ 

	}

	GameObject::GameObject(const std::string &path)
		:m_meshes(),
		 m_shader(Renderer::GetDefaultShader()),
		 m_material(Renderer::GetDefaultMaterial())
	{ 
		Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);	

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        IRON_CORE_ASSERT(false, fmt::format("ERROR::ASSIMP::{}", import.GetErrorString()));
    }
    m_dir = path.substr(0, path.find_last_of('/'));
    ProcessNode(scene->mRootNode, scene);
	}

	GameObject::GameObject(const std::vector<std::shared_ptr<Mesh>> &meshes) 
		:m_meshes(meshes),
		 m_shader(Renderer::GetDefaultShader()),
		 m_material(Renderer::GetDefaultMaterial())
	{

	}

	GameObject::GameObject(const GameObject &go) 
		:m_meshes(go.m_meshes),
		 m_shader(Renderer::GetDefaultShader()),
		 m_material(Renderer::GetDefaultMaterial())
	{

	}

	GameObject::~GameObject() { }

	void GameObject::Draw()
	{
		m_shader->SetMat4x4("model", m_transform.GetMatrix());
		m_material->ApplyMaterial(m_shader);

		for(auto& m : m_meshes)
		{
			Renderer::Submit(m_shader, m->m_vertexArray);
		}
	}

	void GameObject::ProcessNode(aiNode *node, const aiScene *scene)
	{
		// process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      m_meshes.push_back(ProcessMesh(mesh, scene));
    }

    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
			ProcessNode(node->mChildren[i], scene);
    }
	}

	std::shared_ptr<Mesh> GameObject::ProcessMesh(aiMesh *mesh, const aiScene *scene)
	{
		std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
			Vertex vertex;
			vertex.Position.x = mesh->mVertices[i].x;
			vertex.Position.y = mesh->mVertices[i].y;
			vertex.Position.z = mesh->mVertices[i].z;

			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;

			if(mesh->mTextureCoords[0])
			{
				vertex.TexCoords.x = mesh->mTextureCoords[0][i].x; 
				vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);  
			}
			vertices.push_back(vertex);
    }
		
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for(unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
		}    

		ProcessMaterial(mesh, scene);
		
    return std::make_shared<Mesh>(vertices, indices);
	}

	void GameObject::ProcessMaterial(aiMesh *mesh, const aiScene *scene)
	{
		if(mesh->mMaterialIndex >= 0)
    {
      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
			
			std::vector<std::shared_ptr<Texture2D>> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, TEX_ALBEDO);

			if (diffuseMaps.size() > 0)
			{
				m_material->SetAlbedo(diffuseMaps[0]);
				for(unsigned int j = 0; j < m_texturesLoaded.size(); j++)
				{
					bool in = false;
					// If not already loaded
					if(std::strcmp(m_texturesLoaded[j]->GetPath().data(), "backpack/1001_AO.jpg") == 0)
					{
						in = true;
					}
					if (j == m_texturesLoaded.size() - 1 && !in)
					{
						std::shared_ptr<Texture2D> ao = std::make_shared<Texture2D>(TEX_AO, "backpack/1001_AO.jpg", false);
						m_texturesLoaded.push_back(ao);
						m_material->SetAO(ao);
					}
				}
			}
    }
	}

	std::vector<std::shared_ptr<Texture2D>> GameObject::LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName)
	{
		std::vector<std::shared_ptr<Texture2D>> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
			aiString str;
			mat->GetTexture(type, i, &str);
			bool skip = false;
			std::string path = fmt::format("{}/{}", m_dir, str.C_Str()).c_str();

			for(unsigned int j = 0; j < m_texturesLoaded.size(); j++)
			{
				// TODO: Refactor
				if(std::strcmp(m_texturesLoaded[j]->GetPath().data(), path.c_str()) == 0)
				{
					textures.push_back(m_texturesLoaded[j]);
					skip = true;
					break;
				}
			}
			if(!skip)
			{
				std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(typeName, path.c_str(), false);
				m_texturesLoaded.push_back(texture);
				textures.push_back(m_texturesLoaded.back());
			}
		}
    return textures;
	}

	Transform &GameObject::GetTransform()
	{
		return m_transform;
	}

	const std::shared_ptr<Material> &GameObject::GetMaterial()
	{
		return m_material;
	}

	/* static */
	GameObject GameObject::Load(const std::string &path)
	{
		return GameObject(path);
	}

	/* static */
	GameObject GameObject::CreateEmpty() { return GameObject(); }

	/* static */
	GameObject GameObject::Create(Primitives primitive)
	{
		switch(primitive)
		{
			case Primitives::Plane:
			{
				std::vector<Vertex> vBuffer = {
																				{{-1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, 
																				{{ 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, 
																				{{-1.0f, 0.0f,-1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, 
																				{{ 1.0f, 0.0f,-1.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}
																			};
				std::vector<unsigned int> iBuffer = { 0, 1, 2, 2, 3, 1 };
				std::vector<Texture2D> tBuffer = { Texture2D(std::string("texture_diffuse"), "./../../../res/textures/grass.jpeg", true) };

				std::vector<std::shared_ptr<Mesh>> meshes = { std::make_shared<Mesh>(vBuffer, iBuffer) };

				return GameObject(meshes);
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

				std::vector<Texture2D> tBuffer = { };

				std::vector<std::shared_ptr<Mesh>> meshes = { std::make_shared<Mesh>() };

				return GameObject(meshes);
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