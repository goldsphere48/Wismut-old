#include "wipch.h"
#include "Texture.h"

#include "RendererAPI.h"
#include "Wismut/Core/Assert.h"
#include "Wismut/Platform/OpenGL/OpenGLTexture2D.h"

namespace Wi
{
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			WI_CORE_ASSERT(false, "Unspecified render API");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(filepath);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
