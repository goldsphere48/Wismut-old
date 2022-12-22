#include "wipch.h"
#include "Wismut/Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

namespace Wi
{
	namespace Utils
	{
		static GLenum ShaderTypeFromString(const std::string& shaderType)
		{
			if (shaderType == "vertex")
				return GL_VERTEX_SHADER;

			if (shaderType == "fragment")
				return GL_FRAGMENT_SHADER;

			WI_CORE_ASSERT(false, "Unknown shader type");

			return 0;
		}

		std::string_view ConvertGLTypeToString(GLint type)
		{
			switch (type) {
			case GL_FLOAT:
				return "float";
			case GL_FLOAT_VEC2:
				return "float vec2";
			case GL_FLOAT_VEC3:
				return "float vec3";
			case GL_FLOAT_VEC4:
				return "float vec4";
			case GL_DOUBLE:
				return "double";
			case GL_INT:
				return "int";
			case GL_UNSIGNED_INT:
				return "unsigned int";
			case GL_BOOL:
				return "bool";
			case GL_FLOAT_MAT2:
				return "float mat2";
			case GL_FLOAT_MAT3:
				return "float mat3";
			case GL_FLOAT_MAT4:
				return "float mat4";
			default:
				return "?";
			}
		}
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		CreateProgram(std::move(sources));
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		const std::filesystem::path path(filepath);
		m_Name = path.stem().string();
		auto shaderSources = SplitShader(ReadFile(filepath));
		CreateProgram(std::move(shaderSources));
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RenderID);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_RenderID);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(GetLocation(name), value);
	}

	void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		glUniform1i(GetLocation(name), value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* value, uint32_t count)
	{
		glUniform1iv(GetLocation(name), count, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::PrintActiveUniforms()
	{
		GLint numUniforms;
		glGetProgramInterfaceiv(m_RenderID, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

		GLenum properties[] = {GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX};
		WI_CORE_INFO("Active uniforms:");

		for (int i = 0; i < numUniforms; ++i)
		{
			GLint results[4];
			glGetProgramResourceiv(m_RenderID, GL_UNIFORM, i, 4, properties, 4, nullptr, results);

			GLint nameBufferSize = results[0] + 1;
			char* name = new char[nameBufferSize];
			glGetProgramResourceName(m_RenderID, GL_UNIFORM, i, nameBufferSize, nullptr, name);

			WI_CORE_INFO("Name: {0}, Type: {1}, Location: {2}, Block index: {3}", name, Utils::ConvertGLTypeToString(results[1]), results[2], results[3]);

			delete[] name;
		}
	}

	void OpenGLShader::PrintActiveAttributes()
	{
		GLint numAttributes;
		glGetProgramInterfaceiv(m_RenderID, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttributes);

		GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
		WI_CORE_INFO("Active attributes:");

		for (int i = 0; i < numAttributes; ++i)
		{
			GLint results[3];
			glGetProgramResourceiv(m_RenderID, GL_PROGRAM_INPUT, i, 3, properties, 3, nullptr, results);

			GLint nameBufferSize = results[0] + 1;
			char* name = new char[nameBufferSize];
			glGetProgramResourceName(m_RenderID, GL_PROGRAM_INPUT, i, nameBufferSize, nullptr, name);

			WI_CORE_INFO("Name: {0}, Type: {1}, Location: {2}", name, Utils::ConvertGLTypeToString(results[1]), results[2]);

			delete[] name;
		}
	}

	uint32_t OpenGLShader::GetLocation(const std::string name)
	{
		if (m_CachedLocations.find(name) == m_CachedLocations.end())
			m_CachedLocations[name] = glGetUniformLocation(m_RenderID, name.c_str());

		return m_CachedLocations[name];
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::SplitShader(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		std::string typeToken = "#type";
		size_t typeTokenLength = typeToken.size();
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			WI_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			WI_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			WI_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos);

			shaderSources[Utils::ShaderTypeFromString(type)] =
				pos == std::string::npos ?
				source.substr(nextLinePos) :
				source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;
	}

	void OpenGLShader::CreateProgram(std::unordered_map<GLenum, std::string>&& sources)
	{
		const uint32_t program = glCreateProgram();
		WI_CORE_ASSERT(sources.size() <= 2, "Unsupported count of shader types");
		std::array<uint32_t, 2> shaderIDs;

		int shaderIndex = 0;
		for (auto [type, source] : sources)
		{
			uint32_t id = glCreateShader(type);
			const char* src = source.c_str();
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);

			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);

			if (result == GL_FALSE)
			{
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* message = new char[length];
				glGetShaderInfoLog(id, length, &length, message);
				WI_CORE_ERROR("Failed to complile shader: {0}", type == GL_VERTEX_SHADER ? "vertex" : "fragment");
				WI_CORE_ERROR(message);

				glDeleteShader(id);
				glDeleteProgram(program);

				WI_CORE_ASSERT(false, "Failed to complile shader: {0}", type == GL_VERTEX_SHADER ? "vertex" : "fragment");

				delete[] message;
			}

			glAttachShader(program, id);
			shaderIDs[shaderIndex++] = id;
		}

		glLinkProgram(program);
		glValidateProgram(program);

		for (const auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		int status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);

		if (status == GL_FALSE)
		{
			int length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			char* message = new char[length];
			glGetShaderInfoLog(program, length, &length, message);
			WI_CORE_ERROR("Failed to link shader program");
			WI_CORE_ERROR(message);

			glDeleteProgram(program);

			WI_CORE_ASSERT(false, "Failed to link shader program");
		}

		m_RenderID = program;
	}
}
