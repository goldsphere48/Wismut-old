#include "wipch.h"
#include "RendererAPI.h"

#include "Wismut/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wi
{
	RendererAPI::API RendererAPI::s_API = API::OpenGL;

	std::unique_ptr<RendererAPI> RendererAPI::Create()
	{
		switch (GetAPI())
		{
			case API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case API::OpenGL:
				return std::make_unique<OpenGLRendererAPI>();
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
