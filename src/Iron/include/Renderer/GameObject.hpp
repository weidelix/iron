#pragma once

#include "Renderer/Components/Material.hpp"
#include "Renderer/Components/Mesh.hpp"
#include "Renderer/Components/Transform.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/Texture2D.hpp"
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
		IEShader &m_shader;
		IEMaterial m_material;
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		std::vector<IETexture2D> m_texturesLoaded;
		Transform m_transform;
		std::string m_dir;

		GameObject();
		GameObject(const std::string &path);
		void ProcessNode(aiNode *node, const aiScene *scene);
		std::shared_ptr<Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene);
	
	public:
		GameObject(const std::vector<std::shared_ptr<Mesh>> &meshes);
		GameObject(const GameObject &go);
		~GameObject();
		
		void Draw();
		Transform& GetTransform();
		void SetMaterial(const std::shared_ptr<Material> &material);
		const std::shared_ptr<Material> &GetMaterial();
		void SetShader(const std::shared_ptr<Shader> &shader);
		const std::shared_ptr<Shader> &GetShader();
		
		static GameObject Load(const std::string &path);
		static GameObject CreateEmpty();
		static GameObject Create(Primitives primitive);
	};
}