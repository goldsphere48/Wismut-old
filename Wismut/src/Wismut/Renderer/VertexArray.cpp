#include "wipch.h"
#include "Wismut/Renderer/VertexArray.h"
#include "Wismut/Renderer/Renderer.h"
#include "Wismut/Platform/OpenGL/OpenGLVertexArray.h"

namespace Wi
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexArray>();
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
