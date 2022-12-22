#include "wipch.h"
#include "UniformBuffer.h"
#include "RendererAPI.h"
#include "Wismut/Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Wi
{
	Ref<UniformBuffer> UniformBuffer::Create(size_t size, uint8_t binding)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:
			WI_CORE_ASSERT(false, "Unspecified render API");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLUniformBuffer>(size, binding);
		}

		WI_CORE_ASSERT(false, "Unknown render API");
		return nullptr;
	}
}
