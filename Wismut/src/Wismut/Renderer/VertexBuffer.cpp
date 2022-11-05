#include "wipch.h"
#include "VertexBuffer.h"

#include "Renderer.h"
#include "Wismut/Core/Assert.h"
#include "Wismut/Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Wi
{
	namespace Render
	{
		std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
		{
			switch (Renderer::GetAPI())
			{
				case RenderAPI::None:
					WI_CORE_ASSERT(false, "Unspecified render API");
					return nullptr;
				case RenderAPI::OpenGL:
					return std::make_shared<OpenGL::VertexBuffer>(vertices, size);
			}

			WI_CORE_ASSERT(false, "Unknown render API");
			return nullptr;
			
		}

		std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
		{
			switch (Renderer::GetAPI())
			{
				case RenderAPI::None:
					WI_CORE_ASSERT(false, "Unspecified render API");
					return nullptr;
				case RenderAPI::OpenGL:
					return std::make_shared<OpenGL::VertexBuffer>(size);
			}

			WI_CORE_ASSERT(false, "Unknown render API");
			return nullptr;
		}
	}
}
