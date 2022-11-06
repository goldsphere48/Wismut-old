#include "wipch.h"
#include "IndexBuffer.h"

#include "Renderer.h"
#include "Wismut/Core/Assert.h"
#include "Wismut/Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Wi
{
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
