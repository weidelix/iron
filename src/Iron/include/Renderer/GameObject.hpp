#pragma once

#include "Renderer/Components/Mesh.hpp"
#include "Renderer/Components/Transform.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <memory>
namespace Iron
{
	enum Primitives
	{
		Plane,
		Cube,
		Sphere,
		Cone,
		Cylinder
	};
	
	class IRON_API GameObject
	{
	private:
		const std::shared_ptr<Shader>& m_shader;
		const std::shared_ptr<Material>& m_material;
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		std::vector<std::shared_ptr<Texture2D>> m_texturesLoaded;
		Transform m_transform;
		std::string m_dir;

		GameObject();
		GameObject(const std::string &path);
		void ProcessNode(aiNode *node, const aiScene *scene);
		std::shared_ptr<Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene);
		void ProcessMaterial(aiMesh *mesh, const aiScene *scene);
		std::vector<std::shared_ptr<Texture2D>> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
	
	public:
		GameObject(const std::vector<std::shared_ptr<Mesh>> &meshes);
		GameObject(const GameObject &go);
		~GameObject();
		
		void Draw();
		Transform& GetTransform();
		const std::shared_ptr<Material> &GetMaterial();
		
		static GameObject Load(const std::string &path);
		static GameObject CreateEmpty();
		static GameObject Create(Primitives primitive);
	};
}