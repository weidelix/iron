#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Renderer.h"
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <glad/glad.h>


struct ShaderSource
{
	std::string vertex;
	std::string fragment;

	static ShaderSource ParseShaderSource(const std::string& shaderPath);
};

class Shaders
{
private:
	unsigned int m_RendererId;
	unsigned int vertexShaderId;
	unsigned int fragmentShaderId;

public:
	Shaders(const char *vertex, const char *fragment);
	Shaders(const std::string &vertex, const std::string &fragment);
	Shaders(ShaderSource source);
	~Shaders();

	unsigned int CompileShader(unsigned int type, const std::string& sourcecode);
	unsigned int CompileShader(unsigned int type, const char* source);
	void CreateShader(const std::string& vertex, const std::string& fragment);

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

	void Use();
	void Remove();
	void Delete();
};