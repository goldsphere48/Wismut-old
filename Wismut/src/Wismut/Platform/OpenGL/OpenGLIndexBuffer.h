#pragma once
#include "Wismut/Renderer/IndexBuffer.h"

namespace Wi
{
	namespace Render
	{
		namespace OpenGL
		{
			class IndexBuffer : public Render::IndexBuffer
			{
			public:
				IndexBuffer(uint32_t* indices, uint32_t count);
				~IndexBuffer() override;

				void Bind() const override;
				void Unbind() const override;

				uint32_t GetCount() const override { return m_Count; }

			private:
				unsigned int m_RenderID;
				uint32_t m_Count;
			};
		}
	}
}
