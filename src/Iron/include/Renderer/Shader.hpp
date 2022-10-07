#pragma once

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include "pch.hpp"
#include "Core.hpp"
#include <unordered_map>

namespace Iron 
{
	class Shader;
}

using IEShader = std::shared_ptr<Iron::Shader>;
#define CREATE_SHADER(name, vertex, fragment) std::make_shared<Iron::Shader>(name, vertex, fragment)

namespace Iron
{
	class Shader
	{
	private:
		std::vector<unsigned int> m_shaderIds;
		unsigned int m_rendererID;
		std::string m_name;

	public:
		Shader(const std::string &path);
		Shader(const std::string &name, const std::string &path);
		Shader(const std::string &name, const std::string &vertexSource, const std::string &fragmentSouce);
		~Shader();

		void Compile(std::unordered_map<unsigned int, std::string> &Shaderources);
		static std::string ReadFile(const std::string &path);
		std::unordered_map<unsigned int, std::string> Preprocess(std::string &file);
		std::string& GetName();

		void SetInt1(const char *name, int val1);
		void SetInt2(const char *name, int val1, int val2);
		void SetInt3(const char *name, int val1, int val2, int val3);
		void SetInt4(const char *name, int val1, int val2, int val3, int val4);
		void SetFloat1(const char *name, float val1);
		void SetFloat2(const char *name, float val1, float val2);
		void SetFloat3(const char *name, float val1, float val2, float val3);
		void SetFloat4(const char *name, float val1, float val2, float val3, float val4);
		void SetBool(const char *name, bool val1);
		void SetMat4x4(const char* name, const glm::mat4& matrix);
		unsigned int Id() const;
		void Use() const;
		void Remove();
		void Delete();
	};

	class ShaderLibrary
	{
	private:	
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaderLib;

	public:
		void Add(const std::shared_ptr<Shader> &shader);
		void Add(const std::string &name, const std::shared_ptr<Shader> &shader);
		std::shared_ptr<Shader>& Load(const std::string &path);
		std::shared_ptr<Shader>& Load(const std::string &name, const std::string &path);
		std::shared_ptr<Shader>& Load(const std::string &name, const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
		std::shared_ptr<Shader>& Get(const std::string &name);
		bool Exists(const std::string &name);
	};
}