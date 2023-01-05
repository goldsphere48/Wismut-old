#include "wipch.h"
#include "Wismut/Renderer/Shader.h"
#include "Wismut/Renderer/Renderer.h"
#include "Wismut/Platform/OpenGL/OpenGLShader.h"

namespace Wi
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPIType::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPIType::OpenGL:
				return CreateRef<OpenGLShader>(filepath);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSource)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPIType::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPIType::OpenGL:
				return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSource);
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
