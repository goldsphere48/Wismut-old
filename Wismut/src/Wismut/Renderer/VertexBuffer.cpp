#include "wipch.h"
#include "VertexBuffer.h"
#include "Wismut/Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Wi
{
	namespace Render
	{
		std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
		{
			return std::make_shared<OpenGL::VertexBuffer>(vertices, size);
		}

		std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
		{
			return std::make_shared<OpenGL::VertexBuffer>(size);
		}
	}
}
