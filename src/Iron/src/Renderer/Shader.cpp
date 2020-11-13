#include "Renderer/Shaders.h"

Shaders::Shaders(const char* vertex, const char* fragment)
{
	std::cout << "Use \"std::string\" for for passing shader code" << std::endl;
}

Shaders::Shaders(const std::string& vertex, const std::string& fragment)
{
	CreateShader(vertex, fragment);
	glUseProgram(m_RendererId);
}

Shaders::Shaders(ShaderSource source)
{
	CreateShader(source.vertex, source.fragment);
	glUseProgram(m_RendererId);
}

Shaders::~Shaders()
{
	GlCall(glDeleteProgram(m_RendererId));
}

unsigned int Shaders::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GlCall(glShaderSource(id, 1, &src, nullptr));
	GlCall(glCompileShader(id));
	int result;
	GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length;
		GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* log = (char*)_alloca(length * sizeof(char));
		GlCall(glGetShaderInfoLog(id, length, &length, log));
		std::cout << "[GL ERROR] " << (type == GL_VERTEX_SHADER ? "Vertex " : "Fragment ")
			<< "Shader: " << log << std::endl;
		GlCall(glDeleteShader(id));

		return 0;
	}
	else
		std::cout << "[SUCCESS] Compilation successful!" << std::endl;

	return id;
}

unsigned int Shaders::CompileShader(unsigned int type, const char* source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source;
	GlCall(glShaderSource(id, 1, &src, nullptr));
	GlCall(glCompileShader(id));
	int result;
	GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length;
		GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* log = (char*)_alloca(length * sizeof(char));
		GlCall(glGetShaderInfoLog(id, length, &length, log));
		std::cout << "[GL ERROR] " << (type == GL_VERTEX_SHADER ? "Vertex " : "Fragment ")
			<< "Shader: " << log << std::endl;
		GlCall(glDeleteShader(id));

		return 0;
	}
	else
		std::cout << "[SUCCESS] Compilation successful!" << std::endl;

	return id;
}

void Shaders::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	m_RendererId		= glCreateProgram();
	vertexShaderId		= CompileShader(GL_VERTEX_SHADER, vertexShader);
	fragmentShaderId	= CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GlCall(glAttachShader(m_RendererId, vertexShaderId));
	GlCall(glAttachShader(m_RendererId, fragmentShaderId));
	GlCall(glLinkProgram(m_RendererId));
	GlCall(glValidateProgram(m_RendererId));

	GlCall(glDeleteShader(vertexShaderId));
	GlCall(glDeleteShader(fragmentShaderId));
}
// Int
void Shaders::SetInt1(const char *name, int val1)
{
	glUniform1i(glGetUniformLocation(m_RendererId, name), val1);
}

void Shaders::SetInt2(const char* name, int val1, int val2)
{
	glUniform2i(glGetUniformLocation(m_RendererId, name), val1, val2);
}

void Shaders::SetInt3(const char* name, int val1, int val2, int val3)
{
	glUniform3i(glGetUniformLocation(m_RendererId, name), val1, val2, val3);
}

void Shaders::SetInt4(const char* name, int val1, int val2, int val3, int val4)
{
	glUniform4i(glGetUniformLocation(m_RendererId, name), val1, val2, val3, val4);
}
// Float
void Shaders::SetFloat1(const char *name, float val1)
{
	glUniform1f(glGetUniformLocation(m_RendererId, name), val1);
}

void Shaders::SetFloat2(const char *name, float val1, float val2)
{
	glUniform2f(glGetUniformLocation(m_RendererId, name), val1, val2);
}

void Shaders::SetFloat3(const char *name, float val1, float val2, float val3)
{
	glUniform3f(glGetUniformLocation(m_RendererId, name), val1, val2, val3);
}

void Shaders::SetFloat4(const char *name, float val1, float val2, float val3, float val4)
{
	glUniform4f(glGetUniformLocation(m_RendererId, name), val1, val2, val3, val4);
}
// Boolean
void Shaders::SetBool(const char *name, bool val1)
{
	glUniform1i(glGetUniformLocation(m_RendererId, name), val1);
}

void Shaders::SetMat4x4(const char* name, glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(m_RendererId, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shaders::Use()
{
	GlCall(glUseProgram(m_RendererId));
}

void Shaders::Remove()
{
	GlCall(glUseProgram(0));
}

void Shaders::Delete()
{
	GlCall(glDeleteProgram(m_RendererId));
}

unsigned int Shaders::Id() const
{
	return m_RendererId;
}

// ShaderSource

ShaderSource ShaderSource::ParseShaderSource(const std::string& shaderPath)
{
	std::ifstream stream(shaderPath, std::ios::in);
	std::string line;
    
	enum class Shaderintype
	{
		NONE = -1,
		VERintEX = 0,
		FRAGMENint = 1,
	};

	std::stringstream ss[2];
	Shaderintype type = Shaderintype::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = Shaderintype::VERintEX;
			}

			else if (line.find("fragment") != std::string::npos)
			{
				type = Shaderintype::FRAGMENint;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
     
	return { ss[0].str(), ss[1].str() };
}
