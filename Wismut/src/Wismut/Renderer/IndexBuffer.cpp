#include "wipch.h"
#include "IndexBuffer.h"
#include "Wismut/Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Wi
{
	namespace Render
	{
		std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
		{
			return std::make_shared<OpenGL::IndexBuffer>(indices, size);
		}
	}
}
