#include "wipch.h"
#include "IndexBuffer.h"

#include "Renderer.h"
#include "Wismut/Core/Assert.h"
#include "Wismut/Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Wi
{
	namespace Render
	{
		std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
		{
			switch (Renderer::GetAPI())
			{
				case RenderAPI::None: 
					WI_CORE_ASSERT(false, "Unspecified render API");
					return nullptr;
				case RenderAPI::OpenGL:
					return std::make_shared<OpenGL::IndexBuffer>(indices, size);
			}

			WI_CORE_ASSERT(false, "Unknown render API");
			return nullptr;
		}
	}
}
