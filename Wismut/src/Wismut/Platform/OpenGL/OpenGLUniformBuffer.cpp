#include "wipch.h"
#include "OpenGLUniformBuffer.h"
#include <glad/glad.h>

namespace Wi
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(size_t size, uint8_t binding)
		: m_Binding(binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_RendererID);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, uint32_t offset, size_t size)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}
}
