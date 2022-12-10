#include "wipch.h"
#include "Wismut/Renderer/VertexBuffer.h"
#include "Wismut/Renderer/Renderer.h"
#include "Wismut/Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Wi
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;

	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::None:
				WI_CORE_ASSERT(false, "Unspecified render API");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return CreateRef<OpenGLVertexBuffer>(size);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
