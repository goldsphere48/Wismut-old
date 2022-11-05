#include "wipch.h"
#include "OpenGLVertexBuffer.h"
#include "glad/glad.h"

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			VertexBuffer::VertexBuffer(const void* data, uint32_t size)
			{
				glCreateBuffers(1, &m_RenderID);
				glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
				glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			}

			VertexBuffer::VertexBuffer(uint32_t size)
			{
				glCreateBuffers(1, &m_RenderID);
				glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
				glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			}

			VertexBuffer::~VertexBuffer()
			{
				glDeleteBuffers(1, &m_RenderID);
			}

			void VertexBuffer::Bind() const
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
			}

			void VertexBuffer::Unbind() const
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			void VertexBuffer::SetData(const void* data, uint32_t size)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_RenderID);
				glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
			}

			void VertexBuffer::SetLayout(const BufferLayout& layout)
			{
				m_Layout = layout;
			}

			const BufferLayout& VertexBuffer::GetLayout() const
			{
				return m_Layout;
			}
		}
	}
}
