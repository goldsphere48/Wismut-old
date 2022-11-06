#pragma once
#include "Wismut/Renderer/VertexBuffer.h"

namespace Wi
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* data, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);

		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;
		void SetData(const void* data, uint32_t size) override;
		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() const override;

	private:
		uint32_t m_RenderID;
		BufferLayout m_Layout;
	};
}
