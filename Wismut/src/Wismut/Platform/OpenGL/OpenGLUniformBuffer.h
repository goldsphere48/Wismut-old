#pragma once
#include "Wismut/Renderer/UniformBuffer.h"

namespace Wi
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(size_t size, uint8_t binding);
		~OpenGLUniformBuffer() override;

		void SetData(const void* data, uint32_t offset, size_t size) override;

	private:
		uint8_t m_Binding;
		uint32_t m_RendererID;
	};
}
