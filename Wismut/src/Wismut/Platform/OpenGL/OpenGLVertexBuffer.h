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

			private:
				unsigned int m_RenderID;
			};
		}
	}
}
