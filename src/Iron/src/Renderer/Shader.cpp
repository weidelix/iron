#include <glad/glad.h>
#include "Log.hpp"
#include "Renderer/RenderCommand.hpp"
#include <fstream>

static GLenum StringToShaderType(std::string &type)
{
	if (type == "vertex")
		return GL_VERTEX_SHADER;
	if (type == "fragment" || type == "pixel")
		return GL_FRAGMENT_SHADER;
	
	IRON_CORE_ASSERT(false, "Shader type invalid");
	return 0;
}

static std::string ShaderTypeToString(GLenum type)
{
	if (type == GL_VERTEX_SHADER)
		return "vertex";
	if (type == GL_FRAGMENT_SHADER)
		return "fragment";
	
	IRON_CORE_ASSERT(false, "Shader type invalid");
	return 0;
}

namespace Iron
{
	Shader::Shader(const std::string &path)
	{
		std::string file = ReadFile(path);
		std::unordered_map<GLenum, std::string> sources = Preprocess(file);
		Compile(sources);
		glUseProgram(m_rendererID);

		auto lastSlash = path.find_last_of("/\\");
		lastSlash = (lastSlash == std::string::npos) 
			? 0 
			: lastSlash + 1;

		auto lastDot = path.rfind(".");

		auto count = (lastDot == std::string::npos) 
			? file.size() - lastSlash 
			: lastDot - lastSlash;

		m_name = file.substr(lastSlash, count);
		IRON_CORE_INFO(m_name.c_str()); 
	}

	Shader::Shader(const std::string &name, const std::string &path)
		: m_name(name)
	{
		std::string file = ReadFile(path);
		std::unordered_map<GLenum, std::string> sources = Preprocess(file);
		Compile(sources);
		glUseProgram(m_rendererID);
	}

	Shader::Shader(const std::string &name, const std::string &vertexSource, 
								 const std::string &fragmentSource)
		: m_name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
		glUseProgram(m_rendererID);
	}

	Shader::~Shader()
	{
		GlCall(glDeleteProgram(m_rendererID));
	}

	void Shader::Compile(std::unordered_map<GLenum, std::string>& Shaderources)
	{
		std::array<GLenum, 2> glShaderIds;
		int shaderIdIndex = 0;
		GLuint program = glCreateProgram();
		
		for (auto &kv : Shaderources)
		{
			GLuint type = kv.first;
			const std::string& source = kv.second;

			unsigned int shader = glCreateShader(type);

			const GLchar* sourceCstr = source.c_str();
			GlCall(glShaderSource(shader, 1, &sourceCstr, NULL));
			GlCall(glCompileShader(shader));
			
			GLint compileStatus;
			GlCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus));

			if (compileStatus == GL_FALSE)
			{
				int length;
				GlCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length));

				std::vector<char> log(length);
				GlCall(glGetShaderInfoLog(shader, length, &length, log.data()));

				GlCall(glDeleteShader(shader));
				IRON_CORE_ASSERT(false, "{0} shader failed to compile. error {1}", ShaderTypeToString(type), log.data());
				break;
			}
			
			glAttachShader(program, shader);
			glShaderIds[shaderIdIndex++] = shader;
		}


		GlCall(glLinkProgram(program));
		GLint isLinked = 0;
		GlCall(glGetProgramiv(program, GL_LINK_STATUS, &isLinked));
		if (isLinked == GL_FALSE)
		{
			GLint length = 0;
			GlCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length)); 

			std::vector<char> log(length);
			GlCall(glGetShaderInfoLog(program, length, &length, &log[0]));

			GlCall(glDeleteProgram(program));
			
			for (auto id : glShaderIds)
			{
				GlCall(glDeleteShader(id));
			}

			IRON_CORE_ASSERT(false, "Shader program failed to link. error {}", log.data());
			return;
		}

		for (auto id : glShaderIds)
		{
			GlCall(glDetachShader(program, id));
			GlCall(glDeleteShader(id));
		}
		
		m_rendererID = program;
	}

	std::string Shader::ReadFile(const std::string &path)
	{
		std::ifstream stream(path, std::ios::in | std::ios::binary);
		std::string file;
		
		if (stream)
		{
			stream.seekg(0, std::ios::end);
			file.resize(stream.tellg());
			stream.seekg(0, std::ios::beg);
			stream.read(&file[0], file.size());
			stream.close();
		}
		else
		{
			IRON_CORE_ASSERT(false, "Failed to load shader in '{}'", path);
		}
		
		return file;
	}

	std::unordered_map<GLenum, std::string> Shader::Preprocess(std::string& file)
	{
		std::unordered_map<GLenum, std::string> Shaderources;

		const char* typeToken = "#shader";
		size_t typeTokenSize = strlen(typeToken);
		size_t pos = file.find(typeToken, 0);

		while(pos != std::string::npos)
		{
			size_t eol = file.find_first_of("\r\n", pos);
			IRON_CORE_ASSERT(eol, "Syntax error!");
			size_t begin = pos + typeTokenSize + 1;
			std::string type = file.substr(begin, eol - begin);
			IRON_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Shader type invalid!");

			size_t nextLinePos = file.find_first_not_of("\r\n", eol);
			pos = file.find(typeToken, nextLinePos);
			Shaderources[StringToShaderType(type)] = file.substr(nextLinePos, pos -  nextLinePos);
		}

		return Shaderources;
	}

	std::string& Shader::GetName()
	{
		return m_name;
	}

	// Int
	void Shader::SetInt1(const char *name, int val1)
	{
		GlCall(glUniform1i(glGetUniformLocation(m_rendererID, name), val1));
	}

	void Shader::SetInt2(const char* name, int val1, int val2)
	{
		GlCall(glUniform2i(glGetUniformLocation(m_rendererID, name), val1, val2));
	}

	void Shader::SetInt3(const char* name, int val1, int val2, int val3)
	{
		GlCall(glUniform3i(glGetUniformLocation(m_rendererID, name), val1, val2, val3));
	}

	void Shader::SetInt4(const char* name, int val1, int val2, int val3, int val4)
	{
		GlCall(glUniform4i(glGetUniformLocation(m_rendererID, name), val1, val2, val3, val4));
	}
	// Float
	void Shader::SetFloat1(const char *name, float val1)
	{
		GlCall(glUniform1f(glGetUniformLocation(m_rendererID, name), val1));
	}

	void Shader::SetFloat2(const char *name, float val1, float val2)
	{
		GlCall(glUniform2f(glGetUniformLocation(m_rendererID, name), val1, val2));
	}

	void Shader::SetFloat3(const char *name, float val1, float val2, float val3)
	{
		GlCall(glUniform3f(glGetUniformLocation(m_rendererID, name), val1, val2, val3));
	}

	void Shader::SetFloat4(const char *name, float val1, float val2, float val3, float val4)
	{
		GlCall(glUniform4f(glGetUniformLocation(m_rendererID, name), val1, val2, val3, val4));
	}
	// Boolean
	void Shader::SetBool(const char *name, bool val1)
	{
		GlCall(glUniform1i(glGetUniformLocation(m_rendererID, name), val1));
	}

	void Shader::SetMat4x4(const char* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_rendererID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::Use() const
	{
		GlCall(glUseProgram(m_rendererID));
	}

	void Shader::Remove()
	{
		GlCall(glUseProgram(0));
	}

	void Shader::Delete()
	{
		GlCall(glDeleteProgram(m_rendererID));
	}

	unsigned int Shader::Id() const
	{
		return m_rendererID;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader> &shader)
	{
		std::string& shaderName = shader->GetName();
		IRON_CORE_ASSERT(m_shaderLib.find(shaderName) == m_shaderLib.end(), "This shader already exist");
		m_shaderLib[shaderName] = shader;
	}

	void ShaderLibrary::Add(const std::string &name, const std::shared_ptr<Shader> &shader)
	{
		IRON_CORE_ASSERT(m_shaderLib.find(name) == m_shaderLib.end(), "This shader already exist");
		m_shaderLib[name] = shader;
	}

	std::shared_ptr<Shader>& ShaderLibrary::Load(const std::string &path)
	{
		auto shader = std::make_shared<Shader>(path);
		Add(shader);

		return Get(shader->GetName());
	}
	
	std::shared_ptr<Shader>& ShaderLibrary::Load(const std::string &name, const std::string &path)
	{
		auto shader = std::make_shared<Shader>(name, path);
		Add(name, shader);

		return Get(shader->GetName());
	}
	
	std::shared_ptr<Shader> &ShaderLibrary::Get(const std::string &name)
	{
		IRON_CORE_ASSERT(Exists(name), "Shader does not exist");
		return m_shaderLib[name];
	}

	bool ShaderLibrary::Exists(const std::string &name)
	{
		return m_shaderLib.find(name) != m_shaderLib.end();
	}
}