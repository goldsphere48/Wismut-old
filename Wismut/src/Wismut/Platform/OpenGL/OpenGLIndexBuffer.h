#pragma once
#include "Wismut/Renderer/IndexBuffer.h"

namespace Wi
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RenderID;
		uint32_t m_Count;
	};
}
