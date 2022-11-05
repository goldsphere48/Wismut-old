#include "wipch.h"
#include "Shader.h"

#include "Wismut/Core/Log.h"
#include "Wismut/Platform/OpenGL/OpenGLShader.h"

namespace Wi
{
	namespace Render
	{
		std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
		{
			return std::make_shared<OpenGL::Shader>(filepath);
		}

		std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSource)
		{
			return std::make_shared<OpenGL::Shader>(vertexSrc, fragmentSource);
		}

		std::string Shader::ReadFile(const std::string& filepath)
		{
			std::ifstream in(filepath, std::ios::in);
			std::string result;
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				int size = in.tellg();
				if (size != -1)
				{
					result.resize(size);
					in.seekg(0, std::ios::beg);
					in.read(result.data(), size);
				}
				else
					WI_CORE_ERROR("Unable to read file {0}", filepath);
			}
			else
				WI_CORE_ERROR("Unable to read file {0}", filepath);

			return result;
		}
	}
}
