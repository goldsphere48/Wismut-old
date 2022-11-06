#include "wipch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Wismut/Core/Assert.h"
#include "Wismut/Core/Log.h"
#include "Wismut/Platform/OpenGL/OpenGLShader.h"

namespace Wi
{
	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			WI_CORE_ASSERT(false, "Unspecified render API");
			return nullptr;
		case RenderAPI::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::None:
			WI_CORE_ASSERT(false, "Unspecified render API");
			return nullptr;
		case RenderAPI::OpenGL:
			return std::make_shared<OpenGLShader>(vertexSrc, fragmentSource);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
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
