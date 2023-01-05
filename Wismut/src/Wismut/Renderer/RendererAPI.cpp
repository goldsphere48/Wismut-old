#include "wipch.h"
#include "Wismut/Renderer/RendererAPI.h"
#include "Wismut/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Wi
{
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (GetAPI())
		{
			case RendererAPIType::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPIType::OpenGL:
				return CreateScope<OpenGLRendererAPI>();
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
