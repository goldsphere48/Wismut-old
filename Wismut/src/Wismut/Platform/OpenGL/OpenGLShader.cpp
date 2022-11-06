#include "wipch.h"
#include "OpenGLShader.h"

#include "Wismut/Core/Assert.h"

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
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		CreateProgram(std::move(sources));
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
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
		std::vector<uint32_t> shaderIDs;

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
				WI_CORE_ERROR("Failed to complile shader: {0}", type);
				WI_CORE_ERROR(message);

				glDeleteShader(id);
				glDeleteProgram(program);

				WI_CORE_ASSERT(false, "Failed to compile shader");

				delete[] message;
			}

			glAttachShader(program, id);
			shaderIDs.push_back(id);
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
