#include "wipch.h"
#include "Wismut/Renderer/Texture.h"
#include "Wismut/Renderer/RendererAPI.h"
#include "Wismut/Platform/OpenGL/OpenGLTexture2D.h"

namespace Wi
{
	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPIType::None:
			WI_CORE_ASSERT(false, "Unspecified render API");
			return nullptr;
		case RendererAPIType::OpenGL:
			return CreateRef<OpenGLTexture2D>(filepath);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(int width, int height, const void* data)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPIType::None:
			WI_CORE_ASSERT(false, "Unspecified render API");
			return nullptr;
		case RendererAPIType::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height, data);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
