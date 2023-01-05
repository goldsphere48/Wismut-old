#include "wipch.h"
#include "Wismut/Renderer/IndexBuffer.h"
#include "Wismut/Renderer/Renderer.h"
#include "Wismut/Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Wi
{
	Ref<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPIType::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPIType::OpenGL:
				return CreateRef<OpenGLIndexBuffer>(indices, count);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
