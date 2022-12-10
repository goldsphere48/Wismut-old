#include "wipch.h"
#include "Wismut/Renderer/RendererAPI.h"
#include "Wismut/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wi
{
	RendererAPI::API RendererAPI::s_API = API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (GetAPI())
		{
			case API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case API::OpenGL:
				return CreateScope<OpenGLRendererAPI>();
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
