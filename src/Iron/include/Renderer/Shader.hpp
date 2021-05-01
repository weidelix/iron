#pragma once

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include "pch.hpp"
#include "Core.hpp"
#include <unordered_map>

namespace Iron
{
	class Shader
	{
	private:
		vector<unsigned int> m_shaderIds;
		unsigned int m_RendererId;
		string m_name;

	public:
		Shader(const string &path);
		Shader(const string &name, const string &path);
		Shader(const string &name, const string &vertexSource, const string &fragmentSouce);
		~Shader();

		void Compile(unordered_map<unsigned int, string> &Shaderources);
		string ReadFile(const string &path);
		unordered_map<unsigned int, string> Preprocess(string &file);
		string& GetName();

		void SetInt1(const char *name, int val1);
		void SetInt2(const char *name, int val1, int val2);
		void SetInt3(const char *name, int val1, int val2, int val3);
		void SetInt4(const char *name, int val1, int val2, int val3, int val4);
		void SetFloat1(const char *name, float val1);
		void SetFloat2(const char *name, float val1, float val2);
		void SetFloat3(const char *name, float val1, float val2, float val3);
		void SetFloat4(const char *name, float val1, float val2, float val3, float val4);
		void SetBool(const char *name, bool val1);
		void SetMat4x4(const char* name, glm::mat4& matrix);
		unsigned int Id() const;
		void Use() const;
		void Remove();
		void Delete();
	};

	class ShaderLibrary
	{
	private:	
		unordered_map<string, shared_ptr<Shader>> m_shaderLib;

	public:
		void Add(const shared_ptr<Shader> &shader);
		void Add(const string &name, const shared_ptr<Shader> &shader);
		shared_ptr<Shader>& Load(const string &path);
		shared_ptr<Shader>& Load(const string &name, const string &path);
		shared_ptr<Shader>& Get(const string &name);
		bool Exists(const string &name);
	};
}