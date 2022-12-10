#pragma once
#include "Wismut/Renderer/VertexArray.h"

namespace Wi
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;
		void Bind() const override;
		void Unbind() const override;
		void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& buffer) override;
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};
}
