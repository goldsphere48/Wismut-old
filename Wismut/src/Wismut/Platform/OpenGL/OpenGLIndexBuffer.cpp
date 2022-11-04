#include "wipch.h"
#include "OpenGLIndexBuffer.h"
#include "glad/glad.h"

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
				: m_Count(count)
			{
				glCreateBuffers(1, &m_RenderID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
			}

			IndexBuffer::~IndexBuffer()
			{
				glDeleteBuffers(1, &m_RenderID);
			}

			void IndexBuffer::Bind() const
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
			}

			void IndexBuffer::Unbind() const
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		}
	}
}
