#include "wipch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Wismut/Platform/OpenGL/OpenGLVertexArray.h"

namespace Wi
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
