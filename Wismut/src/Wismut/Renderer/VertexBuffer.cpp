#include "wipch.h"
#include "VertexBuffer.h"

#include "Renderer.h"
#include "Wismut/Core/Assert.h"
#include "Wismut/Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Wi
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;

	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexBuffer>(size);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
