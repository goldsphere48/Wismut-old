#pragma once
#include "Wismut/Renderer/VertexBuffer.h"

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			class VertexBuffer : public Render::VertexBuffer
			{
			public:
				VertexBuffer(const void* data, uint32_t size);
				VertexBuffer(uint32_t size);

				~VertexBuffer() override;

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
	}
}
